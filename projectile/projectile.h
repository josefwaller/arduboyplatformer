#pragma once
#include "../utils/bounding_box.h"
#include "../utils/info.h"

struct Projectile {
  BoundingBox bb;
  v2 vel;
  // Whether the projectile exists
  bool exists;
};

Projectile createProjectile(v2 pos, v2 dir);
void updateProjectile(Projectile* a, Info* i, float delta);
void drawProjectile(Projectile* a, Info* i);
