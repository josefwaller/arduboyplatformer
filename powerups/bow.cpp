#include "powerups/bow.h"
#include "utils/camera.h"
#include "utils/constants.h"
#include "utils/bounding_box.h"
#include "bow_sprite.h"
#include "player/player.h"

void updateBow(Bow* b, Info* i, float delta) {
  float newX;
  i->arduboy->setCursor(20, 20);
  const unsigned int BOW_MOVE_SPEED = 20;
  if (b->isGoingLeft) {
    newX = b->bb.pos.x - BOW_MOVE_SPEED * delta;
  } else {
    newX = b->bb.pos.x + BOW_MOVE_SPEED * delta;
  }
  uint8_t roundedX = floor(newX / 16.0f);
  uint8_t roundedY = floor(b->bb.pos.y / 16.0f);
  if (!b->isGoingLeft)
    roundedX++;
  // Checks if the powerup is going off an edge or bumping into a wall
  if ((uint8_t)i->map[16 * roundedY + roundedX] != TILE_NOTHING || (uint8_t)i->map[16 * (roundedY + 1) + roundedX] == TILE_NOTHING) {
    b->isGoingLeft = !b->isGoingLeft;
  } else {
    b->bb.pos.x = newX;
  }
  // Check if the powerup has hit the player
  if (collides(&b->bb, &i->player->bb)) {
    // Deletes the power up
    // TBA
    i->arduboy->setCursor(32, 32);
    i->arduboy->print("Poewrup");
  }
}

void drawBow(Bow* b, Info* i) {
  v2 drawCoords = getCameraCoords(b->bb.pos, i->camera);
  Sprites::drawExternalMask(drawCoords.x, drawCoords.y, bow_sprite, bow_sprite_mask, 0, 0);
}
