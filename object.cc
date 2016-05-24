#include "object.h"

//destructor
Object::~Object() {}

//return row
int Object::getRow(){
	return row;
}

//return col
int Object::getCol(){
	return col;
}

//set coords of object to row and col
void Object::setCoords(int row, int col){
	this->row = row;
	this->col = col;
}

//get object type
char Object::getType(){
	return type;
}

//sets this->cell to cell
void Object::setCell(Cell* cell){
	this->cell = cell;
}

//return object's cell
Cell* Object::getCell(){
	return cell;
}
