#include "game.h"

#include "phpot.h"
#include <iostream>


bool PHPot::revealed = false;

//constructor
PHPot::PHPot(Game *game){
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = '3';
	//revealed = false;
}

//if picked up, will damage player for 10 hp unless player
//is drow in which case they will be damaged for 15
void PHPot::pickedUp(){
	Player* player = game->getPlayer();
	if(player->getType() == 'd'){
		if(player->getHP() <= 15){
			player->setHP(1);
		}
		else{
			player->setHP(player->getHP()-15);
		}
	} else {
		if(player->getHP() <= 10){
			player->setHP(1);
		}
		else{
			player->setHP(player->getHP()-10);
		}	
	}
	revealed = true;
}

//returns if pot is revealed
bool PHPot::isRevealed(){
	return PHPot::revealed;
}

//switch revealed status
void PHPot::switchRevealed(){
	PHPot::revealed = !PHPot::revealed;
}
