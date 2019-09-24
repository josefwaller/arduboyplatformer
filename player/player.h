#include "../utils/vector2.h"

struct Player {
  v2 pos;
  v2 mom;
};

void updatePlayer(Player* p, float delta);
