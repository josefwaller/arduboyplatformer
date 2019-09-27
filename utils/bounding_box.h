#pragma once
#include "vector2.h"

struct BoundingBox {
  v2 pos;
  v2 size;
};

bool collides(BoundingBox *a, BoundingBox *b);
