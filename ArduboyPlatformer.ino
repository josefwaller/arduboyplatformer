#include <Arduboy2.h>
#include "player.h"
#include "tileset.h"

Arduboy2 a;
Sprites s;
long lastMillis;
int counter;

void setup() {
	a.begin();
  lastMillis = millis();
}


void loop() {
	a.clear();
  for (size_t x = 0; x < 10; x++) {
    a.drawFastHLine(0, 10 * x, 200);
  }
  for (size_t y = 0; y < 16; y++) {
    a.drawFastVLine(16 * y, 0, 100);
  }
  s.drawExternalMask(0, 16, player, player_mask, counter, counter);
  if (millis() - lastMillis >= 250) {
    counter = (counter + 1) % 6;
    lastMillis = millis();
  }
	a.display();
}
