#include "player/player.h"

void updatePlayer(Player* p, float delta) {
  if (p->pos.y < 50) {
    p->mom.y += 100 * delta;
  } else {
    p->mom.y = -100;
  }
  p->pos.y += p->mom.y * delta;
};
