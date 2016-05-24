#ifndef RHPOT_H
#define RHPOT_H
#include "potion.h"

class Game;

class RHPot : public Potion{
public:
	static bool revealed;
	RHPot(Game *game);
	void pickedUp();
	bool isRevealed();
	void switchRevealed();
};

#endif
