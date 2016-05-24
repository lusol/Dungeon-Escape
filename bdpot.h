#ifndef BDPOT_H
#define BDPOT_H
#include "potion.h"

class Game;

class BDPot:public Potion{
public:
	static bool revealed;
	BDPot(Game *game);
 	void  pickedUp();
 	bool isRevealed();
	void switchRevealed();
};

#endif
