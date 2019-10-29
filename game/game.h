#pragma once
#include "../player/player.h"
#include "../enemies/walking_enemy.h"
#include "../powerup/powerup.h"
#include "../projectile/projectile.h"
#include "../utils/info.h"
class Arduboy2;
class Sprites;

const uint8_t POWERUP_ARRAY_SIZE = 3;
const uint8_t PROJECTILE_ARRAY_SIZE = 8;
// Pretty much a utility struct for holding everything in the game
struct Game {
  long lastMillis;
  int counter;
  Player player;
  WalkingEnemy walkingEnemy;
  // The size of the powerup array, i.e. the maximum powerups in existance at the same time
  PowerUp powerUps[POWERUP_ARRAY_SIZE]; 
  Projectile projectiles[PROJECTILE_ARRAY_SIZE];
  Info info;
  char level[16 * 16];
};

void beginGame(Game* g, Arduboy2* a);
void updateGame(Game* g, Sprites* s);
void addProjectile(Game* g, Projectile a);
void initLevel(Game* g);
