#ifndef SHADE_H
#define SHADE_H
#include "player.h"

class Game;

class Shade : public Player{
public:
  Shade(Game *game);
  ~Shade();
  void Attack (std::string direction);
};

#endif

