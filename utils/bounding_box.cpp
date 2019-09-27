#include "utils/bounding_box.h"

bool collides(BoundingBox *a, BoundingBox *b) {
  if (a->pos.x + a->size.x > b->pos.x) {
    if (a->pos.y + a->size.y > b->pos.y) {
      if (a->pos.x < b->pos.x + b->size.x) {
        if (a->pos.y < b->pos.y + b->size.y) {
          return true;
        }
      }
    }
  }
  return false;
}
