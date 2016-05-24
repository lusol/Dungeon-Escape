#include "enemy.h"
#include "elf.h"
#include "player.h"

//constructor
Elf::Elf(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'E';
    atk = 30;
    def = 0;
    hp = 140;
}

//attacks player twice unless player is a drow
void Elf::Attack(Player *player){
    if(player->getType() == 'd'){
      player->Defend(this);
    } else{
      player->Defend(this);
      player->Defend(this);
    }
}
