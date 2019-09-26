#include "enemies/walking_enemy.h"
#include "walking_enemy_sprite.h"
#include <Arduboy2.h>

void updateWalkingEnemy(WalkingEnemy* w, Info* i, float delta) {
}
void drawWalkingEnemy(WalkingEnemy* w, Info* i) {
  Sprites::drawExternalMask(w->pos.x, w->pos.y, walking_enemy_sprite, walking_enemy_sprite_mask, 0, 0);
}
