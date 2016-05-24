#include "enemy.h"
#include "player.h"
#include "merchant.h"
#include <cmath>
#include <vector>
#include <sstream>
 
 //return atk
int Enemy::getAtk(){
    return atk;
}
 
//return def
int Enemy::getDef(){
    return def;
}

//return if hp is less than or equal to 0 
bool Enemy::isDead(){
    return hp <= 0;
}
 
//set this->hp to hp 
void Enemy::setHP(int hp){
    if (hp < 0) hp = 0;
    this->hp = hp;
}

//return hp
int Enemy::getHP(){
    return hp;
}
 
//destructor 
Enemy::~Enemy(){}

//randomly moves enemy to a neighbour if possible
void Enemy::Move(){
    std::vector<Cell *> temp;

    //check all cells that are free
    for(int i = 0; i < 8; i++){
        if(cell->getNeighbours()[i]->getBaseType() == '.' && cell->getNeighbours()[i]->getObject() == NULL){
            temp.push_back(cell->getNeighbours()[i]);
        }
    }
    
    if(temp.size() == 0){
        return;
    }
    
    cell->removeObject();
    cell = temp.at(game->rng(temp.size()));
    row = cell->getRow();
    col = cell->getCol();
    cell->setObject(this);
    
}

//defend from player attack, have 50% chance to dodge if enemy 
//is halfling, otherwise take damage
bool Enemy::Defend(Player *player){
    if(type == 'L'){
        if(game->rng(2) == 1){
            player->atkEnemy(this);
            return true;
        } else {
            std::ostringstream oss;
            oss << "PC missed " << type << ".";
            std::string s = oss.str();
            game->updateAction(s);
            return false;
        }
    }
    else{
        if (type == 'M') Merchant::aggressive = true;
        player->atkEnemy(this);
        return true;
    }
}

//calculate how much damage player takes, if player health
//is below 0, end game.
void Enemy::atkPlayer(Player *player){
    int damage = ceil(((100/float(100+ player->getDef()))) * getAtk());
    player->setHP(player->getHP() - damage);

    std::ostringstream oss;
    oss << getType() << " deals " << damage << " to PC.";
    std::string s = oss.str();
    game->updateAction(s);

    if(player->getHP() <= 0){
        game->gameOver();
    }
}
