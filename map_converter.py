from xml.etree import ElementTree
from convert_utils import to_c_code
import sys

def convert_map(src, dest):
    tree = ElementTree.parse(src)
    data = tree.find('layer').find('data')
    hex_data = list(map(lambda x: hex(int(x) - 1), data.text.split(',')))
    c_str = to_c_code(hex_data, dest.split('.')[0], False, True)
    with open(dest, 'w+') as f:
        f.write(c_str)

if __name__ == '__main__':
    convert_map(sys.argv[1], sys.argv[2])
