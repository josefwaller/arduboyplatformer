#include <Arduboy2.h>
#include "test.h"

Arduboy2 a;

void setup() {
	a.begin();
}

void loop() {
	a.clear();
	a.drawBitmap(0, 0, test_bin, 16, 48, WHITE);
	a.display();
}
