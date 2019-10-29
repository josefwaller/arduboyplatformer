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
  g->info.game = g;
  initLevel(g);
}
void updateGame(Game* g, Sprites* s) {
  // Get some values to avoid having g-> everywhere
  Player* p = &g->player;
  Info* info = &g->info;
  WalkingEnemy* we = &g->walkingEnemy;
  Arduboy2* a = g->info.arduboy;
  v2 camera = g->info.camera;
  info->arduboy->pollButtons();
  float delta = (millis() - g->lastMillis) / 1000.0f;
  g->lastMillis = millis();
  for (size_t x = 0; x < 10; x++) {
    a->drawFastHLine(-camera.x + 0, -camera.y + 16 * x, 200);
  }
  for (size_t y = 0; y < 16; y++) {
    a->drawFastVLine(-camera.x + 16 * y, -camera.y + 0, 100);
  }
  // Draw the tile map slowly
  for (size_t y = 0; y < 5; y++) {
    for (size_t x = 0; x < 10; x++) {
      uint8_t tile_index = g->info.map[y * 16 + x];
      // Check that the tile is not -1 (i.e. no tile)
      if (tile_index != 0xFF) {
        s->drawOverwrite(x * 16 - camera.x, y * 16 - camera.y, tileset, tile_index);
      }
    }
  }
  if (p->bb.pos.x > 30) {
    info->camera.x = p->bb.pos.x - 30;
  } else {
    info->camera.x = 0;
  }
  if (p->isDead) {
    a->setCursor((WIDTH - (9 * 6)) / 2, HEIGHT / 2 - 7);
    a->print("You died.");
    a->setCursor((WIDTH - (11 * 6)) / 2, HEIGHT / 2);
    a->print("Start Over?");
    if (a->pressed(A_BUTTON)) {
      initLevel(g);
    }
  }
  updatePlayer(p, info, delta);
  updateWalkingEnemy(we, info, delta);
  for (uint8_t i = 0; i < POWERUP_ARRAY_SIZE; i++) {
    if (g->powerUps[i].exists) {
      updatePowerUp(&g->powerUps[i], info, delta);
    }
  }
  for (size_t i = 0; i < PROJECTILE_ARRAY_SIZE; i++) {
    if (g->projectiles[i].exists) {
      updateProjectile(&g->projectiles[i], info, delta);
    }
  }
  // Check for collisions
  // This should really be in a function eventually
  if (collides(&p->bb, &we->bb) && !we->isDead && !p->isDead) {
    if (p->bb.pos.y - we->bb.pos.y < -5) {
      we->isDead = true;
      p->vel.y = -40;
      if (a->pressed(A_BUTTON)) {
        p->vel.y = -100;
      }
    } else {
      p->isDead = true;
    }
  }
  a->setCursor(0, 0);
  a->print(delta * 1000.0f);
  drawPlayer(p, info);
  drawWalkingEnemy(we, info);
  for (uint8_t i = 0; i < POWERUP_ARRAY_SIZE; i++) {
    if (g->powerUps[i].exists) {
      drawPowerUp(&g->powerUps[i], info);
    }
  }
  for (uint8_t i = 0; i < PROJECTILE_ARRAY_SIZE; i++) {
    if (g->projectiles[i].exists) {
      drawProjectile(&g->projectiles[i], info);
    }
  }
}

void initLevel(Game* g) {
  v2 playerPos = { 33, 16 };
  g->player = createPlayer(playerPos);
  v2 walkingEnemyPos = { 65, 33 };
  g->walkingEnemy = createWalkingEnemy(walkingEnemyPos);
  v2 bpos = {0, 2 * 16};
  g->powerUps[0] = createBow(bpos);
  v2 apos = {32, 16};
  g->projectiles[0] = createProjectile(apos, apos);
  // Copy the level
  for (size_t i = 0; i < 16 * 16; i++) {
    g->level[i] = pgm_read_byte(&test_map[i]);
  }
  g->info.map = g->level;
  g->info.player = &g->player;
}

void addProjectile(Game* g, Projectile a) {
  // Worst case scenario, just does not add a projectile
  for (size_t i = 0; i < PROJECTILE_ARRAY_SIZE; i++) {
    if (!g->projectiles[i].exists) {
      g->projectiles[i] = a;
      break;
    }
  }
}
