#ifndef DRAGONTREASURE_H
#define DRAGONTREASURE_H
#include "treasure.h"

class Dragon;

class DragonTreasure : public Treasure{
	Dragon *dragon;
public:
	DragonTreasure(Game *game, int val);
	void spawnDragon();
	void dragonDied();
	void pickedUp();
};

#endif
