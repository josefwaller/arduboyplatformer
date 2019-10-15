#include "player/player.h"
#include "utils/constants.h"
#include "utils/camera.h"
#include <stdint.h>
#include <Arduboy2.h>
#include <math.h>
#include "bin_sprites/player_sprite.h"

Player createPlayer(v2 pos) {
  return {
    {
      pos,
      { 12, 11 }
    },
    { 0, 0 },
    false,
    false,
    false,
    false,
    PLAYER_STAND
  };
}

void updatePlayer(Player* p, Info* i, float delta) {
  if (p->isDead)
    return;
  if (p->isGrounded) {
    // Check if p has become not grounded
    int roundedX = floor(p->bb.pos.x / 16.0f);
    int roundedY = floor(p->bb.pos.y / 16.0f) + 1;
    int roundedXS = floor((p->bb.pos.x + p->bb.size.x) / 16.0f);
    uint8_t tile = i->map[16 * roundedY + roundedX];
    uint8_t tile2 = i->map[16 * roundedY + roundedXS];
    if (tile == TILE_NOTHING && tile2 == TILE_NOTHING) {
      p->isGrounded = false;
    }
    // Check if the player is jumping
    if (i->arduboy->pressed(A_BUTTON)) {
      p->isGrounded = false;
      p->vel.y = -100;
    }
  } else {
    if (i->arduboy->pressed(A_BUTTON)) {
      p->vel.y += 150 * delta;
    } else {
      p->vel.y += 300 * delta;
    }
  }
  p->vel.x = 0;
  p->isRunning = false;
  if (i->arduboy->pressed(RIGHT_BUTTON)) {
    p->vel.x = 40;
    p->isRunning = true;
    p->facingLeft = false;
    updateAnimation(&p->anim, 150, 3);
  }
  if (i->arduboy->pressed(LEFT_BUTTON)) {
    p->vel.x = -40;
    p->isRunning = true;
    p->facingLeft = true;
    updateAnimation(&p->anim, 150, 3);
  }
  tryToMove(p, i, delta);
  i->arduboy->setCursor(32, 0);
  i->arduboy->print(p->vel.y * 100);
  i->arduboy->setCursor(70, 0);
  i->arduboy->print(p->bb.pos.y);
};

// Just moves the player based on their velocity
// But will stop them from colliding with things
void tryToMove(Player* p, Info* i, float delta) {
  size_t roundedX = floor(p->bb.pos.x / 16.0f);
  size_t roundedY = floor(p->bb.pos.y / 16.0f);
  size_t roundedXS = floor((p->bb.pos.x + p->bb.size.x) / 16.0f);
  size_t roundedYS = floor((p->bb.pos.y + p->bb.size.y) / 16.0f);
  i->arduboy->setCursor(110, 0);
  i->arduboy->print(roundedYS);
  i->arduboy->setCursor(110, 40);
  i->arduboy->print(roundedY);
  // Compute the new Y
  if (p->vel.y != 0) {
    float newYPos = p->bb.pos.y + p->vel.y * delta;
    size_t newRoundedY;
    if (p->vel.y < 0) {
      newRoundedY = floor(newYPos / 16.0f);
    } else {
      newRoundedY = floor((newYPos + p->bb.size.y) / 16.0f);
    }
    if (newRoundedY == roundedY) {
      p->bb.pos.y = newYPos;
    } else {
      uint8_t tile = i->map[16 * newRoundedY + roundedX];
      uint8_t tile2 = i->map[16 * newRoundedY + roundedXS];
      if (tile != TILE_NOTHING || tile2 != TILE_NOTHING ) {
        if (p->vel.y > 0) {
          // The only y specific thing here
          p->isGrounded = true;
          p->bb.pos.y = newRoundedY * 16 - p->bb.size.y - 1;
        } else {
          // Check if the player hit a ? block
          if (tile == TILE_ITEM_BLOCK) {
            i->map[16 * newRoundedY + roundedX] = TILE_ITEM_BLOCK_USED;
          }
          if (tile2 == TILE_ITEM_BLOCK) {
            i->map[16 * newRoundedY + roundedXS] = TILE_ITEM_BLOCK_USED;
          }
          p->bb.pos.y = newRoundedY * 16 + 16;
        }
        p->vel.y = 0;
      } else {
        p->bb.pos.y = newYPos;
      }
    }
  }
  // Check if the player has fallen off the screen
  if (p->bb.pos.y > HEIGHT) {
    p->isDead = true;
    return;
  }
  // Compute the new X
  // Since this is pretty much doing the same thing as above, maybe find some
  // way to abstract it?
  if (p->vel.x != 0) {
    float newXPos = p->bb.pos.x + p->vel.x * delta;
    size_t newRoundedX;
    if (p->vel.x < 0) {
      newRoundedX = floor(newXPos / 16.0f);
    } else {
      newRoundedX = floor((newXPos + p->bb.size.x) / 16.0f);
    }
    if (newRoundedX != roundedX) {
      uint8_t tile = i->map[16 * roundedY + newRoundedX];
      uint8_t tile2 = i->map[16 * roundedYS + newRoundedX];
      if (tile != TILE_NOTHING || tile2 != TILE_NOTHING) {
        if (p->vel.x > 0) {
          p->bb.pos.x = newRoundedX * 16 - 1 - p->bb.size.x;
        } else {
          p->bb.pos.x = newRoundedX * 16 + 16;
        }
        p->vel.x = 0;
      } else {
        p->bb.pos.x = newXPos;
      }
    } else {
      p->bb.pos.x = newXPos;
    }
  }
}
void drawPlayer(Player* p, Info* i) {
  v2 off = { -2, -4 };
  uint8_t state;
  if (p->isDead)
    state = PLAYER_DEAD;
  else if (!p->isGrounded)
    state = PLAYER_JUMP;
  else if (p->isRunning)
    state = p->anim.animState + 1;
  else
    state = PLAYER_STAND;
  if (p->facingLeft)
    state += 6;
  v2 drawCoords = getCameraCoords(p->bb.pos, i->camera);
  Sprites::drawExternalMask(drawCoords.x + off.x, drawCoords.y + off.y, player_sprite, player_sprite_mask, state, state);
}
