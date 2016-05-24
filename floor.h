#ifndef FLOOR_H
#define FLOOR_H
#include "cell.h"
#include "chamber.h"
#include <fstream>
#include <iostream>
#include <vector>

const std::string MAPFILE = "map.txt";
class Game;
class Enemy;

class Floor{
  Cell** grid;
  int rowSize;
  int colSize;
  Game* game;
  Chamber chambers[5];
  void addNeighbours (int i, int j);
public:
  Floor(Game* game, int rowSize, int colSize, std::ifstream &ifs);
  Floor(Game* game, int rowSize, int colSize);
  void updateView(int row, int col, char ch);
  Chamber* getChambers();
  std::vector<Enemy *> getEnemyList();
  ~Floor();
};

#endif
