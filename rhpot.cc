#include "rhpot.h"
#include "game.h"
#include <iostream>

bool RHPot::revealed = false; 

//constructor
RHPot::RHPot(Game *game){
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = '0';
	//revealed = false;
}

//if potion is picked up, increase player health by 10, unless
//player is a drow in which case health is increased by 15.
//health cannot go over max health
void RHPot::pickedUp(){
	Player* player = game->getPlayer();
	if(player->getType() == 'd'){
		if(player->getHP() >= 135){
			player->setHP(150);
		}
		else{
			player->setHP(player->getHP()+15);
		}
	} else {
		if(player->getHP() >= player->getMaxHP() - 10){
			player->setHP(player->getMaxHP());
		}
		else{
			player->setHP(player->getHP()+10);
		}	
	}
	revealed = true;
}

//return revealed status
bool RHPot::isRevealed(){
	return RHPot::revealed;
}

//switch revealed status
void RHPot::switchRevealed(){
	RHPot::revealed = !RHPot::revealed;
}
