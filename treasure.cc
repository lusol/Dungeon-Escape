#include "treasure.h"
#include "game.h"
#include "player.h"
#include <iostream>
#include <sstream>

//constructor
Treasure::Treasure(Game *game, int val){
	value = val;
	this->game = game;
	cell = NULL;
	row = -1;
	col = -1;
	type = 'G';
	pickup = true;
}

//increases player's gold by value
void Treasure::pickedUp(){
	Player* player = game->getPlayer();
	player->setGold(player->getGold()+value);

	std::ostringstream oss;
    oss << "PC picks up " << value << " gold.";
    std::string s = oss.str();
    game->updateAction(s);
}

//return if treasure is able to be picked up
bool Treasure::canPickup(){
	return pickup;
}
