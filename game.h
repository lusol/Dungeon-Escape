#ifndef GAME_H
#define GAME_H
#include <fstream>
#include <iostream>
#include "floor.h"
#include "object.h"
#include "player.h"
#include "potion.h"
#include "enemy.h"
#include "dragontreasure.h"

class gameNotification{
public:
	virtual void updateCell(int row, int col, char ch) = 0;
  virtual void gameOver(bool won, int gold) = 0;
  virtual void updateStatus(int hp, int gold, int atk, int def, int floor) = 0;
  virtual void updateAction(std::string s) = 0;
  virtual void skipEnemyTurn() = 0;
};

const int ROWS = 25;
const int COLS = 79;

class Game{
  Floor *floor;
  int floorsCleared;
 	gameNotification* notification;
  std::ifstream *ifs;
  Player *player;
  void spawnAll();
  int spawnStair();
  void spawnPlayer(int stairchamber);
  void spawnObject(Object* object);
  void spawnDragon(DragonTreasure* dragonTreasure);
  void resetBools();
public:
  Game(char race, gameNotification* notification);
  Game(std::ifstream *ifs, char race, gameNotification* notification);
  ~Game();
  int rng(int mod);
  void playerTurn(std::string s);
  void enemyTurn();
	void updateView(int row, int col, char ch);
  void updateStatus();
  void updateAction(std::string s);
  void gameOver();
  void finishedFloor();
  void enemyDead(Enemy* enemy);
  Player* getPlayer();
};

#endif
