#include "player/player.h"
#include "player_sprite.h"
#include <stdint.h>
#include <Arduboy2.h>
#include <math.h>


void updatePlayer(Player* p, Info* i, float delta) {
  if (p->isGrounded) {
    // Check if p has become not grounded
    int roundedX = floor(p->pos.x / 16.0f);
    int roundedY = floor(p->pos.y / 16.0f) + 1;
    uint8_t tile = i->map[16 * roundedY + roundedX];
    i->arduboy->setCursor(0, 40);
    i->arduboy->print(tile);
    if (tile == 0xFF) {
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
    updateAnimation(&p->anim, 150, 3);
  }
  if (i->arduboy->pressed(LEFT_BUTTON)) {
    p->vel.x = -40;
    p->isRunning = true;
    updateAnimation(&p->anim, 150, 3);
  }
  tryToMove(p, i, delta);
  i->arduboy->setCursor(32, 0);
  i->arduboy->print(p->vel.y * 100);
  i->arduboy->setCursor(70, 0);
  i->arduboy->print(p->pos.y);
  i->arduboy->setCursor(0, 20);
  i->arduboy->print(p->pos.y + p->size.y);
};

// Just moves the player based on their velocity
// But will stop them from colliding with things
void tryToMove(Player* p, Info* i, float delta) {
  size_t roundedX = floor(p->pos.x / 16.0f);
  size_t roundedY = floor(p->pos.y / 16.0f);
  size_t roundedXS = floor((p->pos.x + p->size.x) / 16.0f);
  size_t roundedYS = floor((p->pos.y + p->size.y) / 16.0f);
  i->arduboy->setCursor(110, 0);
  i->arduboy->print(roundedYS);
  i->arduboy->setCursor(110, 40);
  i->arduboy->print(roundedY);
  // Compute the new Y
  if (p->vel.y != 0) {
    float newYPos = p->pos.y + p->vel.y * delta;
    size_t newRoundedY;
    if (p->vel.y < 0) {
      newRoundedY = floor(newYPos / 16.0f);
    } else {
      newRoundedY = floor((newYPos + p->size.y) / 16.0f);
    }
    if (newRoundedY == roundedY) {
      p->pos.y = newYPos;
    } else {
      uint8_t tile = i->map[16 * newRoundedY + roundedX];
      uint8_t tile2 = i->map[16 * newRoundedY + roundedXS];
      if (tile != 0xFF || tile2 != 0xFF) {
        if (p->vel.y > 0) {
          // The only y specific thing here
          p->isGrounded = true;
          p->pos.y = newRoundedY * 16 - p->size.y - 1;
        } else {
          p->pos.y = newRoundedY * 16 + 16;
        }
        p->vel.y = 0;
      } else {
        p->pos.y = newYPos;
      }
    }
  }
  // Compute the new X
  // Since this is pretty much doing the same thing as above, maybe find some
  // way to abstract it?
  if (p->vel.x != 0) {
    float newXPos = p->pos.x + p->vel.x * delta;
    size_t newRoundedX;
    if (p->vel.x < 0) {
      newRoundedX = floor(newXPos / 16.0f);
    } else {
      newRoundedX = floor((newXPos + p->size.x) / 16.0f);
    }
    if (newRoundedX != roundedX) {
      uint8_t tile = i->map[16 * roundedY + newRoundedX];
      uint8_t tile2 = i->map[16 * roundedYS + newRoundedX];
      if (tile != 0xFF || tile2 != 0xFF) {
        if (p->vel.x > 0) {
          p->pos.x = newRoundedX * 16 - 1 - p->size.x;
        } else {
          p->pos.x = newRoundedX * 16 + 16;
        }
        p->vel.x = 0;
      } else {
        p->pos.x = newXPos;
      }
    } else {
      p->pos.x = newXPos;
    }
  }
}
void drawPlayer(Player* p, Info* i) {
  v2 off = { -2, -4 };
  uint8_t state;
  if (!p->isGrounded)
    state = PLAYER_JUMP;
  else if (p->isRunning)
    state = p->anim.animState + 1;
  else
    state = PLAYER_STAND;
  Sprites::drawExternalMask(p->pos.x + off.x, p->pos.y + off.y, player_sprite, player_sprite_mask, state, state);
//  i->arduboy->drawRect(p->pos.x, p->pos.y, p->size.x, p->size.y);
}
