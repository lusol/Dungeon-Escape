#ifndef DRAGONTREASURE_H
#define DRAGONTREASURE_H

class dragonTreasure:public Treasure{
	Dragon *dragon;	
	bool dragonSlain;
public:
	dragonTreasure(Game *game, int val);
	void pickedUp();
};

#endif






