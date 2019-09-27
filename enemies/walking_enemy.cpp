#include "enemies/walking_enemy.h"
#include "walking_enemy_sprite.h"
#include <Arduboy2.h>

void updateWalkingEnemy(WalkingEnemy* w, Info* i, float delta) {
  if (!w->isDead) {
    float newX = w->bb.pos.x + w->vel.x * delta;
    int roundedX = floor(newX / 16.0f);
    if (w->vel.x > 0)
      roundedX++;
    int roundedY = floor(w->bb.pos.y / 16.0f);
    uint8_t tile = i->map[16 * (roundedY + 1) + roundedX];
    // Check if the enemy is hitting a wall or walking off an edge
    if (tile == 0xFF) {
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
  Sprites::drawExternalMask(w->bb.pos.x - i->camera.x, w->bb.pos.y - i->camera.y, walking_enemy_sprite, walking_enemy_sprite_mask, 0, 0);
}
