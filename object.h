#ifndef OBJECT_H
#define OBJECT_H

class Game;
class Cell;

class Object {
protected:
	int row, col;
	char type;
	Game* game;
	Cell* cell;
public:
	
	virtual ~Object() = 0;
	int getRow();
	int getCol();
	void setCoords(int row, int col);
	char getType();
	void setCell(Cell* cell);
	Cell* getCell();
};

#endif
