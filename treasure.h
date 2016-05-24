#ifndef TREASURE_H
#define TREASURE_H
#include "item.h"

class Game;

class Treasure : public Item{
protected:
	int value;
	bool pickup;
public:
	Treasure(Game *game, int val);
	virtual bool canPickup();
	virtual void pickedUp();		
};

#endif
