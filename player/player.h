#pragma once
#include "../utils/vector2.h"
#include "../utils/info.h"
#include "../utils/bounding_box.h"
#include "../animation/animation.h"
#include "../powerup/powerup.h"

struct Player {
  BoundingBox bb;
  v2 vel;
  bool isGrounded;
  bool isRunning;
  bool facingLeft;
  bool isDead;
  Animation anim;
  PowerUpType powerUpState;
};

const uint8_t PLAYER_STAND = 0;
const uint8_t PLAYER_JUMP = 3;
const uint8_t PLAYER_DEAD = 5;

Player createPlayer(v2 pos);
void updatePlayer(Player* p, Info* i, float delta);
void drawPlayer(Player* p, Info* i);
void tryToMove(Player* p, Info* i, float delta);
