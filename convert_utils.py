import math

def to_c_code(nums, name, include_size, in_progmem=True):
  return 'const unsigned char %s %s[] = {%s %s};' % (
    ('PROGMEM' if in_progmem else ''),
    name, 
    ('0x10, 0x10,' if include_size else ''),
    ','.join(nums)
  )


def binary_to_hex_array(bin_array):
  to_return = []
  # Build an integer for every 8 bits/1 byte
  for i in range(math.floor(len(bin_array) / 8)):
    v = 0
    for x in range(8):
      v += math.pow(2, x) * bin_array[i * 8 + x]
    to_return.append(hex(int(v)))
  return to_return
