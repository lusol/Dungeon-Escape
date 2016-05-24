#include "goblin.h"
#include "enemy.h"

//constructor
Goblin::Goblin(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'g';
    atk = 15;
    def = 20;
    maxHP = 110;
    hp = 110;
    gold = 0;
    pe = new PotionEffect(atk, def);
}

//goblin attacks in a certain direction, will ask for
//commands if input is invalid
void Goblin:: Attack(std::string direction){
    Cell* newcell;

    if(direction == "no") newcell = cell->getNeighbours()[1];
    else if(direction == "so") newcell = cell->getNeighbours()[5];
    else if(direction == "ea") newcell = cell->getNeighbours()[3];
    else if(direction == "we") newcell = cell->getNeighbours()[7];
    else if(direction == "ne") newcell = cell->getNeighbours()[2];
    else if(direction == "se") newcell = cell->getNeighbours()[4];
    else if(direction == "nw") newcell = cell->getNeighbours()[0];
    else if(direction == "sw") newcell = cell->getNeighbours()[6];
    else {
        game->updateAction("Can't attack there!");
        return;
    }

    Enemy* enemy;
    if (newcell->isEnemy()) enemy = dynamic_cast<Enemy*> (newcell->getObject());
    else {
        game->updateAction("Nothing to attack!");
        return;
    }

    (dynamic_cast<Enemy*> (enemy))->Defend(this);
}
