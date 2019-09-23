from PIL import Image
import sys
import math

def to_c_code(nums, name, include_size):
  return 'const unsigned char PROGMEM %s[] = {%s %s};' % (
    name, 
    ('0x10, 0x10,' if include_size else ''),
    ','.join(list(map(lambda x: str(hex(int(x))), nums)))
  )


# convert some images into the arduboy format
def convert_image(src, dest, is_mask):
  i = Image.open(src)
  size = i.size
  data = []
  for j in range(math.floor(size[1] / 8)):
    for x in range(size[0]):
      for y in range(8):
        c = i.getpixel((x, 8 * j + y))
        if c == (0, 0, 0, 255):
          data.append(0);
        else:
          data.append(1)
  byte_data = []

  # Build an integer for every 8 bits
  for i in range(math.floor(len(data) / 8)):
    v = 0
    for x in range(8):
      v += math.pow(2, x) * data[i * 8 + x]
    byte_data.append(v)
  # Build the string to write
  data_string = to_c_code(byte_data, dest.split('.')[0] , not is_mask)
  # Write to output file
  with open(dest, 'w+') as f:
      f.write(data_string)


if __name__ == '__main__':
  if len(sys.argv) < 3:
    print("Include the source and destionation files")
  else:
    is_mask = sys.argv == 'mask'
    convert_image(sys.argv[1], sys.argv[2], is_mask)
