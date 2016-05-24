#include "cell.h"
#include "floor.h"
#include <iostream>

//constructor
Cell::Cell(){
	floor = NULL;
	row = 0;
	col = 0;
	baseType = 0;
	floor = NULL;
	object[0] = NULL;
	object[1] = NULL;
	//set all of cell's neighbour pointers to null
	for (int i = 0; i < 8; i++){
		neighbours[i] = NULL;
	}
}

//assign cell to floor, initialize cell's coords, and define cell's type
void Cell::init(Floor *floor, int row, int col, char ch){
  this->floor = floor;
  this->row = row;
  this->col = col;
  baseType = ch;
}

//assign objects to cell's object array
void Cell::setObject(Object* object){
	char ch = object->getType();
	if (ch == 's' || ch == 'd' || ch == 'v' || ch == 't' || ch == 'g') ch = '@';
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5') ch = 'P';
	floor->updateView(row, col, ch);
	object->setCell(this);

	if (this->object[0] != NULL) {
		this->object[1] = object;
	} else {
		this->object[0] = object;
	}
}

//returns object in object array
Object* Cell::getObject(){
	if (object[1] == NULL) return object[0];
	else return object[1];	
}

//removes object from object array
void Cell::removeObject(){
	if (object[1] != NULL) {
		object[1] = NULL;
		char ch = object[0]->getType();
		if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5') ch = 'P';
		floor->updateView(row, col, ch);
	} else {
		object[0] = NULL;
		floor->updateView(row, col, baseType);
	}
}

//adds cell to this->cells neighbour array
void Cell::addNeighbour(Cell* neighbour){
	for (int i = 0; i < 8; i++){
		if (neighbours[i] == NULL) {
			neighbours[i] = neighbour;
			return;
		}
	}
}

//returns cell's neighbours
Cell** Cell::getNeighbours(){
	return neighbours;
}

//returns true if cell's object contains an enemy
//false otherwise
bool Cell::isEnemy(){
	if (getObject() == NULL) return false;
	char ch = getObject()->getType();
	return 
	 ch == 'H' ||
	 ch == 'W' ||
	 ch == 'E' ||
	 ch == 'O' ||
	 ch == 'M' ||
	 ch == 'D' ||
	 ch == 'L' ;
}

//returns true if cell's object contains a potion
//false otherwise
bool Cell::isPotion(){
	if (getObject() == NULL) return false;
	char ch = getObject()->getType();
	return 
	 ch == '0' ||
	 ch == '1' ||
	 ch == '2' ||
	 ch == '3' ||
	 ch == '4' ||
	 ch == '5';
}

//returns true if cell's object contains a player
//false otehrwise
bool Cell::isPlayer(){
	if (getObject() == NULL) return false;
	char ch = getObject()->getType();
	return 
	 ch == 's' || 
	 ch == 'd' || 
	 ch == 'v' || 
	 ch == 't' || 
	 ch == 'g';
}

//returns true if cell's object is a treasure, false otherwise
bool Cell::isTreasure(){
	if (getObject() == NULL) return false;
	char ch = getObject()->getType();
	return ch == 'G';
}

//returns true if cell is a floor, door, or corridor
bool Cell::canNavigate(){
	return 	baseType == '.' || baseType == '+' || baseType == '#';
}

//returns cell's row
int Cell::getRow() {return row;}

//returns cell's column
int Cell::getCol() {return col;}

//returns cell's basetype
char Cell::getBaseType() {return baseType;}

//updates cell's basetype to ch
void Cell::setBaseType(char ch){
	this->baseType = ch;
	floor->updateView(row, col, baseType);
}

//destructor
Cell::~Cell(){
	if (!isPlayer()){
		if (object[0] != NULL) delete object[0];
		if (object[1] != NULL) delete object[1];
	}
}
