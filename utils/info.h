#pragma once
#include <Arduboy2.h>
#include "vector2.h"
// General info to be passed to entities
struct Info {
  char *map;
  Arduboy2* arduboy;
  v2 camera;
};
