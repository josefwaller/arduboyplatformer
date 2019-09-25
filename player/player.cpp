#include "player/player.h"
#include <stdint.h>


void updatePlayer(Player* p, Info* i, float delta) {
  // Get the rounded position of the y coordinate
  float rounded = (p->pos.y + 1) / 16.0f;
  // Get the tile at the bottom right
  uint8_t tile = i->map[(int)(16 * rounded + p->pos.x)];
  if (tile != 0xFF) {
    p->mom.y = - 50;
  } else {
    p->mom.y += 100 * delta;
  }
  p->pos.y += p->mom.y * delta;
};
