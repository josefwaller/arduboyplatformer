python3 image_convert.py
xxd -i test.bin > test.h
sed -i 's/char/const char PROGMEM/g' test.h
