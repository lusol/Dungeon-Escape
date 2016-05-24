#ifndef DROW_H
#define DROW_H
#include "player.h"

class Game;
class Enemy;

class Drow : public Player{
public:
  Drow(Game *game);
  void Attack(std::string direction);
};

#endif
