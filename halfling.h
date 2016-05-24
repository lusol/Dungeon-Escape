#ifndef HALFLING_H
#define HALFLING_H

class Game;
class Player;

class Halfling : public Enemy{
    public:
    Halfling(Game *game);
    void Attack(Player *player);
};

#endif
