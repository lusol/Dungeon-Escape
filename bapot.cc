#include "bapot.h"
#include "game.h"
#include <iostream>

bool BAPot::revealed = false;

//constructor
BAPot::BAPot(Game *game){
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = '1';
//	revealed = false;
}

//if the BAPot is picked up, increase the players atk by 5, unless the player is
//a drow, in which case you increase their atk by 7
void BAPot::pickedUp(){
	Player* player = game->getPlayer();
	if(player->getType() == 'd'){
		player->getPotionEffect()->setAtk(player->getPotionEffect()->getAtk()+7);
	} else {
		player->getPotionEffect()->setAtk(player->getPotionEffect()->getAtk()+5);
	}
	this->revealed = true;
}

//return whether BAPot's is revealed or not
bool BAPot::isRevealed(){
	return BAPot::revealed;
}

//change revealed status to opposite
void BAPot::switchRevealed(){
	BAPot::revealed = !BAPot::revealed;
}
