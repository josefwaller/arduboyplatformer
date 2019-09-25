#pragma once
#include "../utils/vector2.h"
#include "../utils/info.h"

struct Player {
  v2 pos;
  v2 mom;
  bool isGrounded;
};

void updatePlayer(Player* p, Info* i, float delta);
