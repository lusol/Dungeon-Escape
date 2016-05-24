#include "enemy.h"
#include "halfling.h"
#include "player.h"

//constructor
Halfling::Halfling(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'L';
    atk = 15;
    def = 20;
    hp = 100;
}

//halfling attacks player
void Halfling::Attack(Player *player){
    player->Defend(this);    
}
