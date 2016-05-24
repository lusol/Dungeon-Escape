#ifndef VIEW_H
#define VIEW_H
#include <iostream>

class View{
  char **grid;
  int rowSize;
  int colSize;
  std::string action, race;
  int hp, gold, atk, def, floor;
public:
  View(int rowSize, int colSize, char race);
  ~View();
  void printout();
  void updateStatus(int hp, int gold, int atk, int def, int floor);
  void updateAction(std::string s);
  void updateCell(int row, int column, char ch);
};

#endif
