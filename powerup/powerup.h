#pragma once
#include "../utils/bounding_box.h"
#include "../utils/info.h"

struct PowerUp {
  BoundingBox bb;
  bool isGoingLeft;
};

void updatePowerUp(PowerUp* b, Info* i, float delta);
void drawPowerUp(PowerUp* b, Info* i);
