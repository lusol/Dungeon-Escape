#include "human.h"
#include "player.h"

//constructor
Human::Human(Game* game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'H';
    atk = 20;
    def = 20;
    hp = 140;
}

//attacks player
void Human::Attack(Player *player){
    player->Defend(this);
}
