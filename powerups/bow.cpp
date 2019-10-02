#include "powerups/bow.h"
#include "bow_sprite.h"

void updateBow(Bow* b, Info* i, float delta) {
}

void drawBow(Bow* b, Info* i) {
  Sprites::drawExternalMask(b->bb.pos.x, b->bb.pos.y, bow_sprite, bow_sprite_mask, 0, 0);
}
