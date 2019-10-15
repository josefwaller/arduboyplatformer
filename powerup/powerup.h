#pragma once
#include "../utils/bounding_box.h"
#include "../utils/info.h"
struct v2;

enum PowerUpType {
  Bow
};

struct PowerUp {
  BoundingBox bb;
  PowerUpType type;
  bool isGoingLeft;
};

PowerUp createBow(v2 pos);
void updatePowerUp(PowerUp* b, Info* i, float delta);
void updateMovingPowerUp(PowerUp* b, Info* i, float delta);
void drawPowerUp(PowerUp* b, Info* i);
