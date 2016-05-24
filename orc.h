#ifndef ORC_H
#define ORC_H

class Player;
class Enemy;

class Orc : public Enemy{
    public:
    Orc(Game *game);
    void Attack(Player *player);
    ~Orc();
};

#endif
