#include "powerup/powerup.h"
#include "utils/camera.h"
#include "utils/constants.h"
#include "utils/bounding_box.h"
#include "bin_sprites/bow_sprite.h"
#include "player/player.h"

PowerUp createBow(v2 pos) {
  return {
    { pos, { 16.0f, 16.0f }},
    PowerUpType::Bow,
    true,
    true
  };
}
void updatePowerUp(PowerUp* p, Info* i, float delta) {
  if (p->type == PowerUpType::Bow) {
    updateMovingPowerUp(p, i, delta);
  }
}
void updateMovingPowerUp(PowerUp* b, Info* i, float delta) {
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
    b->exists = false;
  }
}

void drawPowerUp(PowerUp* b, Info* i) {
  v2 drawCoords = getCameraCoords(b->bb.pos, i->camera);
  if (b->type == PowerUpType::Bow) {
    Sprites::drawExternalMask(drawCoords.x, drawCoords.y, bow_sprite, bow_sprite_mask, 0, 0);
  }
}
