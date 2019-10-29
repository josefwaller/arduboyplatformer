#include "projectile/projectile.h"
#include "bin_sprites/arrow_sprite.h"

Projectile createProjectile(v2 pos, v2 dir) {
  return {
    { pos, { 10, 10 }},
    dir,
    true 
  };
}

void updateProjectile(Projectile* a, Info* i, float delta) {}
void drawProjectile(Projectile* a, Info* i) {
  Sprites::drawExternalMask(a->bb.pos.x - i->camera.x, a->bb.pos.y - i->camera.y, arrow_sprite, arrow_sprite_mask, 0, 0);
}
