#pragma once
#include "../utils/vector2.h"
#include "../utils/info.h"
#include "../utils/bounding_box.h"

struct WalkingEnemy {
  BoundingBox bb;
  v2 vel;
};

void updateWalkingEnemy(WalkingEnemy* w, Info* i, float delta);
void drawWalkingEnemy(WalkingEnemy* w, Info* i);
