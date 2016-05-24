#include "game.h"
#include "shade.h"
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "item.h"
#include "potion.h"
#include "rhpot.h"
#include "phpot.h"
#include "bapot.h"
#include "wapot.h"
#include "bdpot.h"
#include "wdpot.h"
#include "treasure.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

//default constructor used
Game::Game(char race, gameNotification* notification){
	srand(time(NULL));
	this->notification = notification;
	player = Player::PlayerFactory(race, this);
	floor = new Floor(this, ROWS, COLS);
	floorsCleared = 0;
	this->ifs = NULL;
	spawnAll();
	updateStatus();
	resetBools();
}

//constructor used if player inputs own map
Game::Game (ifstream *ifs, char race, gameNotification* notification){
	srand(time(NULL));
	this->notification = notification;
	player = Player::PlayerFactory(race, this);
	this->ifs = ifs;
	floorsCleared = 0;
	floor = new Floor(this, ROWS, COLS, *ifs);
	updateStatus();
	resetBools();
}

//reset list of bool values
void Game::resetBools(){
	Merchant::aggressive = false;
	RHPot::revealed = false;
	BAPot::revealed = false;
	BDPot::revealed = false;
	PHPot::revealed = false;
	WAPot::revealed = false;
	WDPot::revealed = false;
}

//spawns all enemies, potions, stair, and player on map
void Game::spawnAll(){
	spawnPlayer(spawnStair());

	//spawn all potions
	for (int i = 0; i < 10; i++){
		int potionnum = rng(6);
		Object* object;
		if (potionnum == 0) object = new RHPot(this);
		else if (potionnum == 1) object = new PHPot(this);
		else if (potionnum == 2) object = new BAPot(this);
		else if (potionnum == 3) object = new WAPot(this);
		else if (potionnum == 4) object = new BDPot(this);
		else if (potionnum == 5) object = new WDPot(this);
		spawnObject(object);
	}

	//spawn all treasure
	for (int i = 0; i < 10; i++){
		int treasurenum = rng(8);
		Object* object;
		if (treasurenum < 5) object = new Treasure(this, 2);
		else if (treasurenum < 7) object = new Treasure(this, 1);
		else if (treasurenum < 8) object = new DragonTreasure(this, 6);
		if (treasurenum < 7) spawnObject(object);
		else spawnDragon(dynamic_cast <DragonTreasure*> (object));
	}

	//spawn all monsters
	for(int i = 0; i < 20; i++){
		int monsternum = rng(18);
		Object* object;
		if (monsternum < 4) object = new Human(this);
		else if (monsternum < 7) object = new Dwarf(this);
		else if (monsternum < 12) object = new Halfling(this);
		else if (monsternum < 14) object = new Elf(this);
		else if (monsternum < 16) object = new Orc(this);
		else object = new Merchant(this);
		spawnObject(object);
	}
}

//spawn a player on map
void Game::spawnPlayer(int stairchamber){
	int chamberNum = rng(5);
	while (chamberNum == stairchamber) {chamberNum = rng(5);}
	Chamber* chambers = floor->getChambers();
	vector<Cell*> cells = chambers[chamberNum].getCells();
	int cellNum = rng(cells.size());
	cells[cellNum]->setObject(player);
}

//spawn stairs on map
int Game::spawnStair(){
	Chamber* chambers = floor->getChambers();
	int chamberNum = rng(5);
	vector<Cell*> cells = chambers[chamberNum].getCells();
	int cellNum = rng(cells.size());
	cells[cellNum]->setBaseType('\\');

	return chamberNum;
}	

//spawn a dragon
void Game::spawnDragon(DragonTreasure* dragonTreasure){
	Chamber* chambers = floor->getChambers();

	//enter loop
	while(1){
		int chamberNum = rng(5);

		//if all cells in chamber arent occupied by objects
		if (!chambers[chamberNum].getFull()){
			vector<Cell*> cells = chambers[chamberNum].getCells();
			vector<Cell*> valid;

			//make a list of cells that can be occupied
			for (unsigned int i = 0; i < cells.size(); i++){
				if (cells[i]->getObject() == NULL && cells[i]->getBaseType() != '/') valid.push_back(cells[i]);
			}

			//iterate through all free cells in chamber
			for(unsigned int i = 0; i < valid.size(); i++){
				bool isValid = false;
				//check which neighbours of cell are free
				for(int j = 0; j < 8; j++){
					if(valid[i]->getNeighbours()[j]->getBaseType() == '.' && valid[i]->getNeighbours()[j]->getObject() == NULL){
				   		isValid = true;
				    }
				}
				if(!isValid) valid.erase(valid.begin() + i);
			}


			if (valid.size() != 0){
				int cellNum = rng(valid.size());
				valid[cellNum]->setObject(dragonTreasure);
				dragonTreasure->spawnDragon();
				return;
			}
		}
	}
}


void Game::spawnObject(Object* object){
	Chamber* chambers = floor->getChambers();
	while(1){
		int chamberNum = rng(5);
		if (!chambers[chamberNum].getFull()){
			vector<Cell*> cells = chambers[chamberNum].getCells();
			vector<Cell*> valid;
			for (unsigned int i = 0; i < cells.size(); i++){
				if (cells[i]->getObject() == NULL && cells[i]->getBaseType() != '/') valid.push_back(cells[i]);
			}
			int cellNum = rng(valid.size());
			valid[cellNum]->setObject(object);
			return;
		}
	}
}

//return random number
int Game::rng(int mod){
	return rand() % mod;
}

//destructor
Game::~Game(){
	if (floor != NULL) delete floor;
	if (player != NULL) delete player;
}

//call controller updatecell
void Game::updateView(int row, int col, char ch){
	notification->updateCell(row, col, ch);
}

//call controller updateStatus
void Game::updateStatus(){
	notification->updateStatus(player->getHP(), player->getGold(), player->getAtk(), player->getDef(), floorsCleared);	
}

//call controller
void Game::updateAction(string s){
	notification->updateAction(s);
}

//calculates score and calls controller gameover
void Game::gameOver(){
	int score;
	if (player->getType() == 's') score = player->getGold() * 1.5;
	else score = player->getGold();
	notification->gameOver(false, score);
	notification->skipEnemyTurn();
}

//decides what happens if a floor is finished
void Game::finishedFloor(){
	floorsCleared++;
	//if its the fifth floor finished, its gameover
	if (floorsCleared == 5) {
		int score;
		if (player->getType() == 's') score = player->getGold() * 1.5;
		else score = player->getGold();
		notification->gameOver(true, score);
		return;
	}

	//spawn another floor
	delete floor;
	if (ifs == NULL) {
		floor = new Floor(this, ROWS, COLS);
		spawnAll();
	}
	else {
		floor = new Floor(this, ROWS, COLS, *ifs);
	}
	notification->skipEnemyTurn();
	updateAction("Went up the staircase.");
}

//remove enemy from the game if enemy is dead
void Game::enemyDead(Enemy* enemy){
	if (enemy->isDead()){
		enemy->getCell()->removeObject();
		if (enemy->getType() == 'M' || enemy->getType() == 'H') {
			Treasure* treasure = new Treasure(this, 4);
			enemy->getCell()->setObject(treasure);
		} else if (enemy->getType() == 'D'){
			dynamic_cast <Dragon*> (enemy)->getDragonTreasure()->dragonDied();
		}

		int gold = rng(2) + 1;
		if (player->getType() == 'g') gold += 5;
		player->setGold(player->getGold() + gold);

		ostringstream oss;
    	oss << "PC earns " << gold << " gold.";
    	string s = oss.str();
    	updateAction(s);

		delete enemy;
	}
}

//allows player to choose actions
void Game::playerTurn(string s){
	if (s == "a"){
		string direction;
		cin >> direction;
		player->Attack(direction);
	} else if (s == "u") {
		string direction;
		cin >> direction;
		player->Use(direction);	
	} else {
		player->Move(s);
	}

	if(player->getType() == 't'){
		player->setHP(player->getHP() + 5);
	}
}

//return player
Player* Game::getPlayer(){return player;}

//what happens durign enemies turn
void Game::enemyTurn(){
	vector<Enemy *> enemyList = floor->getEnemyList();

	//loop through list of all enemies
	for(unsigned int i = 0; i < enemyList.size(); i++){
		bool attackedPlayer = false;
		//loop through neighbouring cells and check if there is a player on one of the cells
		//if there is a player attack them
		for(int j = 0; j < 8; j++){
			if (enemyList[i]->getCell()->getObject()->getType() == 'D'){
				Cell* temp = static_cast <Dragon *> (enemyList[i])->getDragonTreasure()->getCell()->getNeighbours()[j];
				if(temp->isPlayer()){
					enemyList[i]->Attack(dynamic_cast <Player*> (temp->getObject()));
					break;
				}
			}
			if(enemyList[i]->getCell()->getNeighbours()[j]->isPlayer()){
				enemyList[i]->Attack(dynamic_cast <Player*> (enemyList[i]->getCell()->getNeighbours()[j]->getObject()));
				if (enemyList[i]->getType() == 'M' && !(static_cast <Merchant *> (enemyList[i])->aggressive)){}
				else attackedPlayer = true;
				break;
			}	
		}
		if(!attackedPlayer){
			if (enemyList[i]->getType() != 'D')enemyList[i]->Move();
		}
	}

	updateStatus();
}
