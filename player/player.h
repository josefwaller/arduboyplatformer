#pragma once
#include "../utils/vector2.h"
#include "../utils/info.h"

struct Player {
  v2 pos;
  v2 vel;
  v2 size;
  bool isGrounded;
  uint8_t animState;
};

void updatePlayer(Player* p, Info* i, float delta);
void drawPlayer(Player* p, Info* i);
void tryToMove(Player* p, Info* i, float delta);
