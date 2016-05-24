#include "enemy.h"
#include "dwarf.h"
#include "player.h"

//constructor
Dwarf::Dwarf(Game *game){
     this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'W';
    atk = 20;
    def = 30;
    hp = 100;
}

//attack player, calls player defense
void Dwarf::Attack(Player *player){
    player->Defend(this);
}
