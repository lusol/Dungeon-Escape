#include "vampire.h"
#include "enemy.h"

//constructor
Vampire::Vampire(Game *game){
    this->game = game;
    cell = NULL;
    row = -1;
    col = -1;
    type = 'v';
    atk = 25;
    def = 15;
    maxHP = 0;
    hp = 150;
    gold = 0;
    pe = new PotionEffect(atk, def);

}

//attack enemy in certain direction, if input is invalid, reprompt
void Vampire::Attack(std::string direction){
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

    char type = enemy->getType();
    bool successful = (dynamic_cast<Enemy*> (enemy))->Defend(this);

    //if enemy is a dwarf, subtract 5 hp,
    //else add 5 hp
    if(successful){
        if(type == 'W'){
            setHP(getHP()-5);
        }
        else{
            setHP(getHP()+5);
        }
    }
}
