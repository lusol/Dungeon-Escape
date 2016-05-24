#ifndef ELF_H
#define ELF_H

class Game;
class Player;

class Elf : public Enemy{
    public:
    Elf(Game *game);
    void Attack(Player *player);
};

#endif
