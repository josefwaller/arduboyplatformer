#include <Arduboy2.h>
#include "player/player.h"
#include "tileset.h"
#include "test_map.h"
#include "utils/info.h"
#include "enemies/walking_enemy.h"

Arduboy2 a;
Sprites s;
long lastMillis;
int counter;
Player p;
WalkingEnemy we;
Info info;

void setup() {
	a.begin();
  lastMillis = millis();
  p.bb.pos = { 33, 16 };
  p.bb.size = { 12, 11 };
  we.bb.pos = { 65, 33 };
  we.vel = { 20, 0 };
  info.map = test_map;
  info.arduboy = &a;
}


void loop() {
	a.clear();
  float delta = (millis() - lastMillis) / 1000.0f;
  lastMillis = millis();
  for (size_t x = 0; x < 10; x++) {
    a.drawFastHLine(-info.camera.x + 0, -info.camera.y + 16 * x, 200);
  }
  for (size_t y = 0; y < 16; y++) {
    a.drawFastVLine(-info.camera.x + 16 * y, -info.camera.y + 0, 100);
  }
  // Draw the tile map slowly
  for (size_t y = 0; y < 5; y++) {
    for (size_t x = 0; x < 10; x++) {
      uint8_t tile_index = info.map[y * 16 + x];
      // Check that the tile is not -1 (i.e. no tile)
      if (tile_index != 0xFF) {
        s.drawOverwrite(x * 16 - info.camera.x, y * 16 - info.camera.y, tileset, tile_index);
        a.setCursor(x * 16 - info.camera.x, y * 16 - info.camera.y);
      }
    }
  }
  if (p.bb.pos.x > 30) {
    info.camera.x = p.bb.pos.x - 30;
  } else {
    info.camera.x = 0;
  }
  updatePlayer(&p, &info, delta);
  updateWalkingEnemy(&we, &info, delta);
  a.setCursor(0, 0);
  a.print(delta * 1000.0f);
  drawPlayer(&p, &info);
  drawWalkingEnemy(&we, &info);
	a.display();
}
