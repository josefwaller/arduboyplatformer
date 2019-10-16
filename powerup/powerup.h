#pragma once
#include "../utils/bounding_box.h"
#include "../utils/info.h"
struct v2;

enum PowerUpType {
  Nothing,
  Bow
};

struct PowerUp {
  BoundingBox bb;
  PowerUpType type;
  bool isGoingLeft;
  // Whether the powerup exists
  // Stored here so that it can easily set it to false when used by player
  bool exists;
};

PowerUp createBow(v2 pos);
void updatePowerUp(PowerUp* b, Info* i, float delta);
void updateMovingPowerUp(PowerUp* b, Info* i, float delta);
void drawPowerUp(PowerUp* b, Info* i);
