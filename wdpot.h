#ifndef WDPOT_H
#define WDPOT_H
#include "potion.h"

class Game;

class WDPot:public Potion{
public:
	static bool revealed;
	WDPot(Game *game);
	void pickedUp();
	bool isRevealed();
	void switchRevealed();
};

#endif
