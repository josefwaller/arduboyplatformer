#pragma once
#include "../utils/vector2.h"
#include "../utils/info.h"
#include "../utils/bounding_box.h"
#include "../animation/animation.h"

struct Player {
  BoundingBox bb;
  v2 vel;
  bool isGrounded;
  bool isRunning;
  bool facingLeft;
  Animation anim;
};

const uint8_t PLAYER_STAND = 0;
const uint8_t PLAYER_JUMP = 3;

void updatePlayer(Player* p, Info* i, float delta);
void drawPlayer(Player* p, Info* i);
void tryToMove(Player* p, Info* i, float delta);
