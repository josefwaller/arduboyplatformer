#include <Arduboy2.h>
#include "player.h"
#include "tileset.h"
#include "test_map.h"

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
  // Draw the tile map slowly
  for (size_t y = 0; y < 5; y++) {
    for (size_t x = 0; x < 10; x++) {
      uint8_t tile_index = test_map[y * 16 + x];
      // Check that the tile is not -1 (i.e. no tile)
      if (tile_index != 0xFF) {
        s.drawOverwrite(x * 16, y * 16, tileset, tile_index);
        a.setCursor(x * 16, y * 16);
      }
    }
  }
  s.drawExternalMask(0, 16, player, player_mask, counter, counter);
  if (millis() - lastMillis >= 250) {
    counter = (counter + 1) % 6;
    lastMillis = millis();
  }
	a.display();
}
