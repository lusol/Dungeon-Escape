#ifndef DWARF_H
#define DWARF_H

class Game;
class Player;

class Dwarf : public Enemy{
    public:
    Dwarf(Game *game);
    void Attack(Player *player);
};

#endif
