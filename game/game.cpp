#include "game/game.h"
#include <Arduboy2.h>
#include "player/player.h"
#include "tileset.h"
#include "test_map.h"
#include "utils/info.h"
#include "powerup/powerup.h"
#include "enemies/walking_enemy.h"


void beginGame(Game* g, Arduboy2* a) {
  g->lastMillis = millis();
  g->info.arduboy = a;
  initLevel(g);
}
void updateGame(Game* g, Sprites* s) {
  Arduboy2* a = g->info.arduboy;
  float delta = (millis() - g->lastMillis) / 1000.0f;
  g->lastMillis = millis();
  for (size_t x = 0; x < 10; x++) {
    a->drawFastHLine(-g->info.camera.x + 0, -g->info.camera.y + 16 * x, 200);
  }
  for (size_t y = 0; y < 16; y++) {
    a->drawFastVLine(-g->info.camera.x + 16 * y, -g->info.camera.y + 0, 100);
  }
  // Draw the tile map slowly
  for (size_t y = 0; y < 5; y++) {
    for (size_t x = 0; x < 10; x++) {
      uint8_t tile_index = g->info.map[y * 16 + x];
      // Check that the tile is not -1 (i.e. no tile)
      if (tile_index != 0xFF) {
        s->drawOverwrite(x * 16 - g->info.camera.x, y * 16 - g->info.camera.y, tileset, tile_index);
      }
    }
  }
  if (g->p.bb.pos.x > 30) {
    g->info.camera.x = g->p.bb.pos.x - 30;
  } else {
    g->info.camera.x = 0;
  }
  if (g->p.isDead) {
    a->setCursor((WIDTH - (9 * 6)) / 2, HEIGHT / 2 - 7);
    a->print("You died.");
    a->setCursor((WIDTH - (11 * 6)) / 2, HEIGHT / 2);
    a->print("Start Over?");
    if (a->pressed(A_BUTTON)) {
      initLevel(g);
      g->p.isDead = false;
    }
  }
  updatePlayer(&g->p, &g->info, delta);
  updateWalkingEnemy(&g->we, &g->info, delta);
  for (uint8_t i = 0; i < POWERUP_ARRAY_SIZE; i++) {
    if (g->powerUpExists[i]) {
      updatePowerUp(&g->powerUps[i], &g->info, delta);
    }
  }
  // Check for collisions
  if (collides(&g->p.bb, &g->we.bb) && !g->we.isDead && !g->p.isDead) {
    if (g->p.bb.pos.y - g->we.bb.pos.y < -5) {
      g->we.isDead = true;
      g->p.vel.y = -40;
      if (a->pressed(A_BUTTON)) {
        g->p.vel.y = -100;
      }
    } else {
      g->p.isDead = true;
    }
  }
  a->setCursor(0, 0);
  a->print(delta * 1000.0f);
  drawPlayer(&g->p, &g->info);
  drawWalkingEnemy(&g->we, &g->info);
  for (uint8_t i = 0; i < POWERUP_ARRAY_SIZE; i++) {
    if (g->powerUpExists[i]) {
      drawPowerUp(&g->powerUps[i], &g->info);
    }
  }

}
void initLevel(Game* g) {
  v2 playerPos = { 33, 16 };
  g->p = createPlayer(playerPos);
  v2 walkingEnemyPos = { 65, 33 };
  g->we = createWalkingEnemy(walkingEnemyPos);
  v2 bpos = {0, 2 * 16};
  g->powerUps[0] = createBow(bpos);
  g->powerUpExists[0] = true;
  // Copy the level
  for (size_t i = 0; i < 16 * 16; i++) {
    g->level[i] = pgm_read_byte(&test_map[i]);
  }
  g->info.map = g->level;
  g->info.player = &g->p;
}
