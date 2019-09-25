#include "player/player.h"
#include <stdint.h>
#include <Arduboy2.h>
#include <math.h>


void updatePlayer(Player* p, Info* i, float delta) {
  if (p->isGrounded) {
    // Check if p has become not grounded
    int roundedX = floor(p->pos.x / 16.0f);
    int roundedY = floor(p->pos.y / 16.0f) + 1;
    uint8_t tile = i->map[16 * roundedY + roundedX];
    i->arduboy->setCursor(0, 40);
    i->arduboy->print(tile);
    if (tile == 0xFF) {
      p->isGrounded = false;
    }
    // Check if the player is jumping
    if (i->arduboy->pressed(A_BUTTON)) {
      p->isGrounded = false;
      p->vel.y = -50;
    }
  } else {
    p->vel.y += 50 * delta;
  }
  p->vel.x = 0;
  if (i->arduboy->pressed(RIGHT_BUTTON)) {
    p->vel.x = 20;
  }
  if (i->arduboy->pressed(LEFT_BUTTON)) {
    p->vel.x = -20;
  }
  tryToMove(p, i, delta);
  i->arduboy->setCursor(32, 0);
  i->arduboy->print(p->vel.y * 100);
  i->arduboy->setCursor(70, 0);
  i->arduboy->print(p->pos.y);
  i->arduboy->setCursor(110, 0);
  i->arduboy->print(p->isGrounded);
};

// Just moves the player based on their velocity
// But will stop them from colliding with things
void tryToMove(Player* p, Info* i, float delta) {
  size_t roundedX = floor(p->pos.x / 16.0f);
  size_t roundedY = floor(p->pos.y / 16.0f);
  if (p->vel.y > 0) {
    // check if the new position is stil valid
    uint8_t tile = i->map[(16 * (roundedY + 1) + roundedX)];
    if (tile != 0xFF) {
      p->vel.y = 0.0f;
      p->isGrounded = true;
    } else {
      p->pos.y += p->vel.y * delta;
    }
  } else if (p->vel.y < 0) {
    uint8_t tile = i->map[16 * roundedY + roundedX];
    if (tile != 0xff) {
      p->vel.y = 0.0f;
    } else {
      p->pos.y += p->vel.y * delta;
    }
  }
  if (p->vel.x != 0) {
    float newXPos = p->pos.x + p->vel.x * delta;
    size_t newRoundedX = floor(newXPos / 16.0f);
    if (newRoundedX != roundedX) {
      uint8_t tile = i->map[16 * roundedY + newRoundedX];
      uint8_t tile2 = i->map[16 * (roundedY + 1) + newRoundedX];
      if (tile != 0xFF || tile2 != 0xFF) {
        p->vel.x = 0;
      } else {
        p->pos.x = newXPos;
      }
    } else {
      p->pos.x = newXPos;
    }
  }
}
