#include "enemy.h"
#include "player.h"
#include "orc.h"

//constructor
Orc::Orc(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'O';
    atk = 30;
    def = 25;
    hp = 180;
}

//attack player
void Orc::Attack(Player *player){
    player->Defend(this);
}

//destructor
Orc::~Orc(){}
