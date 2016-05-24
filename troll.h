#ifndef TROLL_H
#define TROLL_H
#include "player.h"

class Game;

class Troll : public Player{
public:
  Troll(Game *game);
  void Attack(std::string direction);
};

#endif
