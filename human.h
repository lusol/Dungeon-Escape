#ifndef HUMAN_H
#define HUMAN_H
#include "enemy.h"

class Game;
class Player;

class Human:public Enemy{
public:
    Human(Game *game);
    void Attack(Player *player);
};

#endif
