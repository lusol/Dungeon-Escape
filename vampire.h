#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "player.h"

class Game;
class Enemy;

class Vampire : public Player{
public:
  Vampire(Game *game);
  void Attack(std::string direction);
};

#endif
