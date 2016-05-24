#include "player.h"
#include "enemy.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "potion.h"
#include "rhpot.h"
#include "phpot.h"
#include "bapot.h"
#include "wapot.h"
#include "bdpot.h"
#include "wdpot.h"
#include "treasure.h"
#include <cmath>
#include <sstream>
#include <iostream>
//destructor
Player::~Player() {delete pe;}

//return max hp
int Player::getMaxHP(){
    return maxHP;
}

//return atk
int Player::getAtk(){
    return pe->getAtk();
}

//return def
int Player::getDef(){
    return pe->getDef();
}

//return current hp
int Player::getHP(){
    return hp;
}

//return gold amount
int Player::getGold(){
    return gold;
}

//set mahp to hp
void Player::setMaxHP(int hp){
    maxHP = hp;
}

//set current hp to hp
void Player::setHP(int newHP){
    if (newHP > hp) hp = maxHP;
    else if (newHP < 0) hp = 0;
    else hp = newHP;
}

//set current gold to gold
void Player::setGold(int gold){
    this->gold = gold;
}

//return potion effect
PotionEffect* Player::getPotionEffect(){
    return pe;
}

//return a pointer to a player depending on the race
//indicated
Player* Player::PlayerFactory(char race, Game* game){
    Player* output;
    switch (race){
    case 's':
        output = new Shade(game);
        break;
    case 'd':
        output = new Drow(game);
        break;
    case 'v':
        output = new Vampire(game);
        break;
    case 'g':
        output = new Goblin(game);
        break;
    case 't':
        output = new Troll(game);
        break;
    default:
        output = new Shade(game);
        break;
    }
    return output;
}

//moves player in a certain direction
void Player::Move(std::string direction){
    Cell* newcell;
    std::string translatedDirection;

    if(direction == "no") {
        newcell = cell->getNeighbours()[1];
        translatedDirection = "North";
    } else if(direction == "so") {
        newcell = cell->getNeighbours()[5];
        translatedDirection = "South";
    } else if(direction == "ea") {
        newcell = cell->getNeighbours()[3];
        translatedDirection = "East";
    } else if(direction == "we") {
        newcell = cell->getNeighbours()[7];
        translatedDirection = "West";
    } else if(direction == "ne") {
        newcell = cell->getNeighbours()[2];
        translatedDirection = "Northeast";
    } else if(direction == "se") {
        newcell = cell->getNeighbours()[4];
        translatedDirection = "Southeast";
    } else if(direction == "nw") {
        newcell = cell->getNeighbours()[0];
        translatedDirection = "Northwest";
    } else if(direction == "sw") {
        newcell = cell->getNeighbours()[6];
        translatedDirection = "Southwest";
    }
    else {
        game->updateAction("Can't move there!");
        return;
    }

    //player has reached a staircase
    if (newcell->getBaseType() == '\\'){
        game->finishedFloor();
        delete pe;
        pe = new PotionEffect(atk, def);
        return;
    } else if(!newcell->isEnemy() && !newcell->isPotion() && newcell->canNavigate()){
        //pick up treasure if its not a dragon hoard
        if (newcell->isTreasure()) {
            Treasure* treasure = dynamic_cast<Treasure*> (newcell->getObject());
            if (treasure->canPickup()){
                dynamic_cast<Treasure*> (treasure)->pickedUp();
                newcell->removeObject();
                delete treasure;
            }
        }
        cell->removeObject();
        newcell->setObject(this);
        game->updateAction("PC moves " + translatedDirection + checkSurroundingPots());
    } else{
        game->updateAction("Can't move there!");
    }
}

//calculate damage done to enemy and check if they are dead
void Player::atkEnemy(Enemy *enemy){
    int damage = ceil(((100/float(100+ enemy->getDef()))) * getAtk());
    enemy->setHP(enemy->getHP() - damage);

    std::ostringstream oss;
    oss << "PC deals " << damage << " to " << enemy->getType() << " (" << enemy->getHP() << " HP).";
    std::string s = oss.str();
    game->updateAction(s);

    game->enemyDead(enemy);
}


//try to use potion within a certain direction, reprompts if commands are invalid
void Player::Use(std::string direction){
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
        game->updateAction("Now is not the time to drink that!");
        return;
    }

    Potion* potion;
    if (newcell->isPotion()) potion = dynamic_cast<Potion*> (newcell->getObject());
    else {
        game->updateAction("Can't drink that!");
        return;
    }

    dynamic_cast<Potion*> (potion)->pickedUp();
    
    std::string potionName;
    char potionNum = potion->getType();
    if (potionNum == '0') potionName = "RH";
    else if (potionNum == '1') potionName = "BA";
    else if (potionNum == '2') potionName = "BD";
    else if (potionNum == '3') {
        potionName = "PH";
        if (getHP() <= 0) game->gameOver();
    } else if (potionNum == '4') potionName = "WA";
    else potionName = "WD";

    game->updateAction("PC used " + potionName + ".");

    potion->getCell()->removeObject();
    delete potion;
}


bool Player::Defend(Enemy *enemy){
    if(game->rng(2) == 0){
        enemy->atkPlayer(this);
        return true;
    } else{
        std::ostringstream oss;
        oss << enemy->getType() << " missed PC.";
        std::string s = oss.str();
        game->updateAction(s);
        return false;
    }
}

std::string Player::checkSurroundingPots(){
    std::string str = "";
    for(int i = 0; i < 8; i++){
        Cell* temp = cell->getNeighbours()[i];
        if(temp->isPotion()){
            if(temp->getObject()->getType() == '0' && RHPot::revealed) str += " and sees a RH";
            else if(temp->getObject()->getType() == '1' && BAPot::revealed) str += " and sees a BA";
            else if(temp->getObject()->getType() == '2' && BDPot::revealed) str += " and sees a BD";
            else if(temp->getObject()->getType() == '3' && PHPot::revealed) str += " and sees a PH";
            else if(temp->getObject()->getType() == '4' && WAPot::revealed) str += " and sees a WA";
            else if(temp->getObject()->getType() == '5' && WDPot::revealed) str += " and sees a WD";
            else str += " and sees an unknown potion";
        }
    }
    str += ".";
    return str;
}
