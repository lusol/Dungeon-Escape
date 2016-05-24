#ifndef CHAMBER_H
#define CHAMBER_H

#include "cell.h"
#include <vector>

class Chamber {
	std::vector<Cell*> cells;
public:	
	Chamber();
	bool getFull();
	void setCells(Cell* cell);
	bool isMember(Cell* cell);
	bool isEmpty();
	std::vector<Cell*>& getCells();
	~Chamber();
};

#endif
