#include "enemy.h"
#include "player.h"
#include "merchant.h"

bool Merchant::aggressive = false;

//constructor
Merchant::Merchant(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'M';
    atk = 70;
    def = 5;
    hp = 30;
}

//attacks player if aggressive
void Merchant::Attack(Player *player){
    if (aggressive) player->Defend(this);
}

//returns aggressive status
bool Merchant::getAggressive(){
    return Merchant::aggressive;
}

//switch aggressive status
void Merchant::switchAggressive(){
    Merchant::aggressive = !Merchant::aggressive;
}
