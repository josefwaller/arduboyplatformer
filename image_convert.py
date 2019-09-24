from PIL import Image
import sys
import math
from convert_utils import to_c_code, binary_to_hex_array

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
  byte_data = binary_to_hex_array(data)
  byte_mask = binary_to_hex_array(mask)
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
