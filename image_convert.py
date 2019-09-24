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
def convert_image(src, dest):
  i = Image.open(src)
  size = i.size
  data = []
  mask = []
  for j in range(math.floor(size[1] / 8)):
    for x in range(size[0]):
      for y in range(8):
        c = i.getpixel((x, 8 * j + y))
        if c[3] == 0:
          mask.append(0)
          data.append(0)
        else:
          mask.append(1)
          if c == (0, 0, 0, 255):
            data.append(0);
          else:
            data.append(1)
  byte_data = []
  byte_mask = []

  # Build an integer for every 8 bits/1 byte
  for i in range(math.floor(len(data) / 8)):
    data_v = 0
    mask_v = 0
    for x in range(8):
      data_v += math.pow(2, x) * data[i * 8 + x]
      mask_v += math.pow(2, x) * mask[i * 8 + x]
    byte_data.append(data_v)
    byte_mask.append(mask_v)
  # Build the string to write
  data_string = to_c_code(byte_data, dest.split('.')[0] , True)
  mask_string = to_c_code(byte_mask, '%s_mask' % dest.split('.')[0], False)
  # Write to output file
  with open(dest, 'w+') as f:
    f.write(data_string)
    f.write(mask_string)


if __name__ == '__main__':
  if len(sys.argv) < 3:
    print("Include the source and destionation files")
  else:
    convert_image(sys.argv[1], sys.argv[2])
