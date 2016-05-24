#ifndef GOBLIN_H
#define GOBLIN_H
#include "player.h"

class Game;

class Goblin : public Player{
public:
  Goblin(Game *game);
  void Attack(std::string direction);
};

#endif
