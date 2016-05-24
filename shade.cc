#include "shade.h"
#include "enemy.h"

//constructor
Shade::Shade(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    atk = 30;
    def = 25;
    type = 's';
    maxHP = 125;
    hp = 125;
    gold = 0;
    pe = new PotionEffect(atk, def);
}

//attack enemy in a certain direction, reprompts if invalid commands are
//input
void Shade::Attack(std::string direction){
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

//destructor
Shade::~Shade(){}
