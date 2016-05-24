#include "dragontreasure.h"
#include "dragon.h"
#include <iostream>
#include <sstream>

//constructor
DragonTreasure::DragonTreasure(Game *game, int val) : Treasure(game, val){
	dragon = NULL;
	pickup = false;	
}

//adds gold to player
void DragonTreasure::pickedUp(){
    game->getPlayer()->setGold(game->getPlayer()->getGold()+value);

    std::ostringstream oss;
    oss << "PC picks up " << value << " gold.";
    std::string s = oss.str();
    game->updateAction(s);
}

//spawns a dragon at an available cell around treasure
void DragonTreasure::spawnDragon(){
	dragon = new Dragon(game, this);
	std::vector<Cell *> temp;
    //checks all neighbours of dragon treasure and add them to vector temp
    for(int i = 0; i < 8; i++){
        if(cell->getNeighbours()[i]->getBaseType() == '.' && cell->getNeighbours()[i]->getObject() == NULL){
            temp.push_back(cell->getNeighbours()[i]);
        }
    }

    int cellnum = game->rng(temp.size());
    dragon->setCell(temp[cellnum]);
    temp[cellnum]->setObject(dragon);
}

//sets pickup to true
void DragonTreasure::dragonDied(){
	pickup = true;
}
