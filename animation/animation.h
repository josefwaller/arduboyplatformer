#pragma once
#include <stdint.h>

struct Animation {
  uint8_t animState;
  long lastChangeMillis;
};

void updateAnimation(Animation* a, const long duration, const uint8_t numOfFrames);
