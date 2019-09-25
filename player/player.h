#pragma once
#include "../utils/vector2.h"
#include "../utils/info.h"
#include "../animation/animation.h"

struct Player {
  v2 pos;
  v2 vel;
  v2 size;
  bool isGrounded;
  bool isRunning;
  Animation anim;
};

const uint8_t PLAYER_STAND = 0;
const uint8_t PLAYER_JUMP = 3;

void updatePlayer(Player* p, Info* i, float delta);
void drawPlayer(Player* p, Info* i);
void tryToMove(Player* p, Info* i, float delta);
