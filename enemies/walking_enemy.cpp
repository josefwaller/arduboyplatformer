#include "enemies/walking_enemy.h"
#include "walking_enemy_sprite.h"
#include "utils/constants.h"
#include "utils/camera.h"
#include <Arduboy2.h>

WalkingEnemy createWalkingEnemy(v2 pos) {
  return {
    {
      pos,
      { 16, 16 }
    },
    { 0, 0 },
    false
  };
}

void updateWalkingEnemy(WalkingEnemy* w, Info* i, float delta) {
  if (!w->isDead) {
    float newX = w->bb.pos.x + w->vel.x * delta;
    int roundedX = floor(newX / 16.0f);
    if (w->vel.x > 0)
      roundedX++;
    int roundedY = floor(w->bb.pos.y / 16.0f);
    uint8_t tile = i->map[16 * (roundedY + 1) + roundedX];
    // Check if the enemy is hitting a wall or walking off an edge
    if (tile == TILE_NOTHING) {
      // Turn around
      w->vel.x *= -1;
    } else {
      i->arduboy->setCursor(40, 40);
      i->arduboy->print(tile);
      w->bb.pos.x = newX;
    }
  } else {
    w->bb.pos.y += 30 * delta;
  }
}

void drawWalkingEnemy(WalkingEnemy* w, Info* i) {
  v2 drawCoords = getCameraCoords(w->bb.pos, i->camera);
  Sprites::drawExternalMask(drawCoords.x, drawCoords.y, walking_enemy_sprite, walking_enemy_sprite_mask, 0, 0);
}
