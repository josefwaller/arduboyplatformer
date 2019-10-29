#pragma once
#include <Arduboy2.h>
#include "vector2.h"
// Forward declaration of player
struct Player;
struct Game;
// General info to be passed to entities
struct Info {
  char *map;
  Arduboy2* arduboy;
  v2 camera;
  Player* player;
  Game* game;
};
