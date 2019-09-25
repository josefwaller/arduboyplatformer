#include <Arduboy2.h>
#include "player_sprite.h"
#include "player/player.h"
#include "tileset.h"
#include "test_map.h"
#include "utils/info.h"

Arduboy2 a;
Sprites s;
long lastMillis;
int counter;
Player p;
Info info;

void setup() {
	a.begin();
  lastMillis = millis();
  p.pos = { 33, 16 };
  p.size = { 12, 11 };
  info.map = test_map;
  info.arduboy = &a;
}


void loop() {
	a.clear();
  float delta = (millis() - lastMillis) / 1000.0f;
  lastMillis = millis();
  for (size_t x = 0; x < 10; x++) {
    a.drawFastHLine(0, 16 * x, 200);
  }
  for (size_t y = 0; y < 16; y++) {
    a.drawFastVLine(16 * y, 0, 100);
  }
  // Draw the tile map slowly
  for (size_t y = 0; y < 5; y++) {
    for (size_t x = 0; x < 10; x++) {
      uint8_t tile_index = info.map[y * 16 + x];
      // Check that the tile is not -1 (i.e. no tile)
      if (tile_index != 0xFF) {
        s.drawOverwrite(x * 16, y * 16, tileset, tile_index);
        a.setCursor(x * 16, y * 16);
      }
    }
  }
  updatePlayer(&p, &info, delta);
  v2 off = { -2, -5 };
  s.drawExternalMask(p.pos.x + off.x, p.pos.y + off.y, player_sprite, player_sprite_mask, counter, counter);
  a.drawRect(p.pos.x, p.pos.y, p.size.x, p.size.y);
  a.setCursor(0, 0);
  a.print(delta * 1000.0f);
	a.display();
}
