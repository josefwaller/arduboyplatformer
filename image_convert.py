from PIL import Image
import math

# convert some images into the arduboy format
def convert_image(src, dest):
	i = Image.open(src)
	size = i.size
	data = []
	mask = []
	for j in range(math.floor(size[1] / 8)):
		for x in range(size[0]):
			for y in range(8):
				print(x, 8 * j + y)
				c = i.getpixel((x, 8 * j + y))
				if c[3] == 0:
					data.append(0)
					mask.append(0)
				else:
					mask.append(1)
					if c == (0, 0, 0, 255):
						data.append(0);
					else:
						data.append(1)
	byte_data = []
	byte_mask = []
	for i in range(math.floor(len(data) / 16)):
		print(''.join(list(map(str, data[16 * i:16 * (i + 1)]))))
	for i in range(math.floor(len(data) / 8)):
		v = 0
		for x in range(8):
			v += math.pow(2, x) * data[i * 8 + x]
		byte_data.append(v)
	print(list(map(lambda x: hex(int(x)), byte_data)))

	with open('test.bin', 'wb') as f:
		for d in byte_data:
			f.write(int(d).to_bytes(1, 'little'))
		
if __name__ == '__main__':
	convert_image('images/player.png', 'converted_images/sprite.bin')
