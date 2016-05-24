#include "dragontreasure.h"
#include "dragon.h"
#include "player.h"

//constructor
Dragon::Dragon(Game *game, DragonTreasure *treasure){
    this->game = game;
    this->treasure = treasure;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'D';
    atk = 20;
    def = 20;
    hp = 150;
}

//attacks player, calls player defend method
void Dragon::Attack(Player *player){
    player->Defend(this);
}

//returns treasure dragon is pointing to
DragonTreasure* Dragon::getDragonTreasure(){
    return treasure;
}
