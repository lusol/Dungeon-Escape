#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"

class Game;
class DragonTreasure;
class Player;

class Dragon : public Enemy{
    DragonTreasure *treasure;
public:
    Dragon(Game *game, DragonTreasure *treasure);
    void Attack(Player *player);
    DragonTreasure* getDragonTreasure();
};

#endif
