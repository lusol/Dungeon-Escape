#include "bdpot.h"
#include "game.h"
#include <iostream>

bool BDPot::revealed = false;

//constructor
BDPot::BDPot(Game *game){
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = '2';
	//revealed = false;
}

//if pot is picked up increase players defense by 5 unless player is a drow, in which
//case you increase defence by 7
void BDPot::pickedUp(){
	Player* player = game->getPlayer();
	if(player->getType() == 'd'){
		player->getPotionEffect()->setDef(player->getPotionEffect()->getDef()+7);
	} else {
		player->getPotionEffect()->setDef(player->getPotionEffect()->getDef()+5);
	}
	revealed = true;
}

//return if pot's revealed status
bool BDPot::isRevealed(){
	return BDPot::revealed;;
}

//switch pot's revealed status
void BDPot::switchRevealed(){
	BDPot::revealed = !BDPot::revealed;
}
