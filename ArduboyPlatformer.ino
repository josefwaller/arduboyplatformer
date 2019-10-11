#include <Arduboy2.h>
#include "player/player.h"
#include "tileset.h"
#include "test_map.h"
#include "utils/info.h"
#include "powerups/bow.h"
#include "enemies/walking_enemy.h"

Arduboy2 a;
Sprites s;
long lastMillis;
int counter;
Player p;
WalkingEnemy we;
Bow b;
Info info;
char level[16 * 16];

void setup() {
	a.begin();
  lastMillis = millis();
  initLevel();
}

void initLevel() {
  v2 playerPos = { 33, 16 };
  p = createPlayer(playerPos);
  v2 walkingEnemyPos = { 65, 33 };
  we = createWalkingEnemy(walkingEnemyPos);
  we.vel = { 20, 0 };
  b.bb.pos = { 4 * 16, 2 * 16 };
  // Copy the level
  for (size_t i = 0; i < 16 * 16; i++) {
    level[i] = pgm_read_byte(&test_map[i]);
  }
  info.map = level;
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
      }
    }
  }
  if (p.bb.pos.x > 30) {
    info.camera.x = p.bb.pos.x - 30;
  } else {
    info.camera.x = 0;
  }
  if (p.isDead) {
    a.setCursor((WIDTH - (9 * 6)) / 2, HEIGHT / 2 - 7);
    a.print("You died.");
    a.setCursor((WIDTH - (11 * 6)) / 2, HEIGHT / 2);
    a.print("Start Over?");
    if (a.pressed(A_BUTTON)) {
      initLevel();
      p.isDead = false;
    }
  }
  updatePlayer(&p, &info, delta);
  updateWalkingEnemy(&we, &info, delta);
  updateBow(&b, &info, delta);
  // Check for collisions
  if (collides(&p.bb, &we.bb) && !we.isDead && !p.isDead) {
    if (p.bb.pos.y - we.bb.pos.y < -5) {
      we.isDead = true;
      p.vel.y = -40;
      if (a.pressed(A_BUTTON)) {
        p.vel.y = -100;
      }
    } else {
      p.isDead = true;
    }
  }
  a.setCursor(0, 0);
  a.print(delta * 1000.0f);
  drawPlayer(&p, &info);
  drawWalkingEnemy(&we, &info);
  drawBow(&b, &info);
	a.display();
}
