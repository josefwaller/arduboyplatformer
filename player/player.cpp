#include "player/player.h"
#include <stdint.h>
#include <Arduboy2.h>
#include <math.h>


void updatePlayer(Player* p, Info* i, float delta) {
  if (p->isGrounded) {
    i->arduboy->setCursor(0, 50);
    i->arduboy->print(i->arduboy->pressed(A_BUTTON));
    if (i->arduboy->pressed(A_BUTTON)) {
      p->isGrounded = false;
      p->mom.y = -50;
    }
  } else {
    // Move the player down
    float rounded = p->pos.y / 16.0f;
    p->mom.y += 50.0f * delta;
    p->pos.y += p->mom.y * delta;
    // check if the new position is stil valid
    // Get the tile at the bottom right
    int roundedY = floor(p->pos.y / 16.0f) + 1;
    int roundedX = floor(p->pos.x / 16.0f);
    uint8_t tile = i->map[(int)(16 * roundedY + roundedX)];
    i->arduboy->setCursor(32, 0);
    i->arduboy->print(tile);
    if (tile != 0xFF) {
      p->mom.y = 0;
      p->isGrounded = true;
    }
  }
  if (i->arduboy->pressed(RIGHT_BUTTON)) {
    p->pos.x += 20 * delta;
  }
  if (i->arduboy->pressed(LEFT_BUTTON)) {
    p->pos.x -= 20 * delta;
  }

};
