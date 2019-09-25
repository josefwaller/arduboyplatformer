#include "player/player.h"
#include <stdint.h>
#include <Arduboy2.h>
#include <math.h>


void updatePlayer(Player* p, Info* i, float delta) {
  if (p->isGrounded) {
    if (i->arduboy->pressed(A_BUTTON)) {
      p->isGrounded = false;
      p->mom.y = -50;
    }
  }
  if (i->arduboy->pressed(RIGHT_BUTTON)) {
    p->pos.x += 20 * delta;
  }
  if (i->arduboy->pressed(LEFT_BUTTON)) {
    p->pos.x -= 20 * delta;
  }
  tryToMove(p, i, delta);
  i->arduboy->setCursor(32, 0);
  i->arduboy->print(p->mom.y * 100);
  i->arduboy->setCursor(70, 0);
  i->arduboy->print(p->pos.y);
  i->arduboy->setCursor(110, 0);
  i->arduboy->print(p->isGrounded);
};

void tryToMove(Player* p, Info* i, float delta) {
  if (!p->isGrounded) {
    // Move the player down
    float rounded = p->pos.y / 16.0f;
    p->mom.y += 50.0f * delta;
    p->pos.y += p->mom.y * delta;
    // check if the new position is stil valid
    // Get the tile at the bottom right
    int roundedY = floor(p->pos.y / 16.0f) + 1;
    int roundedX = floor(p->pos.x / 16.0f);
    uint8_t tile = i->map[(int)(16 * roundedY + roundedX)];
    if (tile != 0xFF) {
      p->mom.y = 0.0f;
      p->isGrounded = true;
    }
  } else {
    // Check if p has become not grounded
    int roundedX = floor(p->pos.x / 16.0f);
    int roundedY = floor(p->pos.y / 16.0f) + 1;
    uint8_t tile = i->map[16 * roundedY + roundedX];
    i->arduboy->setCursor(0, 40);
    i->arduboy->print(tile);
    if (tile == 0xFF) {
      p->isGrounded = false;
    }
  }
}
