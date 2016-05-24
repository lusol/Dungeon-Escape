#include "chamber.h"
#include <iostream>

//chamber constructor
Chamber::Chamber(){}

//returns true if all cell's have atleast one object,
//false otherwise
bool Chamber::getFull(){
	// loop through all cells and check if any of them dont have objecs
	for (unsigned int i = 0; i < cells.size(); i++){
		if (cells[i]->getObject() == NULL) return false;
	}
	return true;
}

//add all cells within a chamber to the the chamber list
void Chamber::setCells(Cell* cell){
	if (cell->getBaseType() == '.') {
		cells.push_back(cell);
		//loop through all available neighbours within a cell and recursively calls setCells
		//on all neighbours that are not members of the chamber list
		for (int i = 0; i < 8; i++){
			if ((cell->getNeighbours())[i] == NULL) break;
			else if (!isMember((cell->getNeighbours())[i])){
				setCells((cell->getNeighbours())[i]);
			}
		}
	}
}

//checks if cell is a member of chamber
bool Chamber::isMember(Cell* cell){
	//loops through all cells in chamber, returns true if cell
	//is one of those cells
	for (unsigned int i = 0; i < cells.size(); i++){
		if (cells[i] == cell) return true;
	}
	return false;
}



//returns true if chamber has no cells, false otherwise
bool Chamber::isEmpty(){
	return cells.size() == 0;
}

//returns chamber's list of cells
std::vector<Cell*>& Chamber::getCells(){
	return cells;
}

//destructor
Chamber::~Chamber(){}
