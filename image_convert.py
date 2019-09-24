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
  # Do every 16x16 block in order
  for img_y in range(math.floor(size[1] / 16)):
      for img_x in range(math.floor(size[0] / 16)):
          # Add the block in rows of 8 pixels each
          # 2 rows of 8 pixel high blocks
          for j in range(2):
            for x in range(16):
              for y in range(8):
                c = i.getpixel((img_x * 16 + x, img_y * 16 + 8 * j + y))
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
