#include "game.h"
#include "wapot.h"
#include <iostream>

bool WAPot::revealed = false;

//constructor
WAPot::WAPot(Game *game){
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = '4';
	//revealed = false;
}

//if picked up, decrease player atk by 5 unless player is a drow,
//in which case decrease atk by 7
void WAPot::pickedUp(){
	Player* player = game->getPlayer();
	if(player->getType() == 'd'){
		player->getPotionEffect()->setAtk(player->getPotionEffect()->getAtk()-7);
	} else {
		player->getPotionEffect()->setAtk(player->getPotionEffect()->getAtk()-5);
	}
	revealed = true;	
}

//return revealed status
bool WAPot::isRevealed(){
	return WAPot::revealed;
}

//change revealed status
void WAPot::switchRevealed(){
	WAPot::revealed = !WAPot::revealed;
}
