#include "game.h"
#include "wdpot.h"
#include <iostream>

bool WDPot::revealed = false;

//constructor
WDPot::WDPot(Game *game){
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = '5';
	//revealed = false;
}

//if picked up, player's defense will decrease by 5 unless player is a drow,
//in which case their defense will decrease by 7
void WDPot::pickedUp(){
	Player* player = game->getPlayer();

	if(player->getType() == 'd'){
		player->getPotionEffect()->setDef(player->getPotionEffect()->getDef()-7);
	} else {
		player->getPotionEffect()->setDef(player->getPotionEffect()->getDef()-5);
	}
	revealed = true;
}

//return revealed status
bool WDPot::isRevealed(){
	return WDPot::revealed;
}

//switch revealed status
void WDPot::switchRevealed(){
	WDPot::revealed = !WDPot::revealed;
}
