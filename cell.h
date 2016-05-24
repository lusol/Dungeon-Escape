#ifndef CELL_H
#define CELL_H
#include "object.h"

class Floor;

class Cell{
  int row, col;
  char baseType;
  Cell* neighbours[8];
  Floor* floor;
  Object* object[2];
public:
  Cell();
  void init(Floor *floor, int row, int col, char ch);
  void setObject(Object* object);
  Object* getObject();
  void removeObject();
  void addNeighbour(Cell* neighbours);
  Cell** getNeighbours();
  char getBaseType();
  void setBaseType(char ch);
  bool isEnemy();
  bool isPotion();
  bool isTreasure();
  bool isPlayer();
  bool canNavigate();
  int getRow();
  int getCol();
  ~Cell();
};

#endif
