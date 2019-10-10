#include "powerups/bow.h"
#include "utils/camera.h"
#include "bow_sprite.h"

void updateBow(Bow* b, Info* i, float delta) {
}

void drawBow(Bow* b, Info* i) {
  v2 drawCoords = getCameraCoords(b->bb.pos, i->camera);
  Sprites::drawExternalMask(drawCoords.x, drawCoords.y, bow_sprite, bow_sprite_mask, 0, 0);
}
