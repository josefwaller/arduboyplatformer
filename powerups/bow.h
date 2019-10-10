#pragma once
#include "../utils/bounding_box.h"
#include "../utils/info.h"

struct Bow {
  BoundingBox bb;
};

void updateBow(Bow* b, Info* i, float delta);
void drawBow(Bow* b, Info* i);