#include "animation/animation.h"
#include <Arduboy2.h>

void updateAnimation(Animation* a, long duration, uint8_t numOfFrames) {
  if (millis() - a->lastChangeMillis >= duration) {
    a->animState = (a->animState + 1) % numOfFrames;
    a->lastChangeMillis = millis();
  }
}
