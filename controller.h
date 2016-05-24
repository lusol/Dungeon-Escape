#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include "view.h"
#include <iostream>

class Controller : gameNotification{
  Game* game;
  std::string fileName;
  View* view;
  void init();
  bool quit, skip;
  std::ifstream* ifs;
public:
  Controller(std::string filename);
  Controller();
  ~Controller();
  void updateStatus(int hp, int gold, int atk, int def, int floor);
  void updateAction(std::string s);
  void updateCell(int row, int col, char ch);
  void gameOver(bool won, int gold);
  void skipEnemyTurn();
  void play();
};

#endif
