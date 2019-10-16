#include <Arduboy2.h>
#include "game/game.h"

Arduboy2 a;
Sprites s;
Game game;

void setup() {
	a.begin();
  beginGame(&game, &a);
}

void loop() {
	a.clear();
  updateGame(&game, &a, &s);
	a.display();
}
