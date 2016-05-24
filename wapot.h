#ifndef WAPOT_H
#define WAPOT_H
#include "potion.h"

class Game;

class WAPot:public Potion{
public:
	static bool revealed;
	WAPot(Game *game);
	void pickedUp();
	bool isRevealed();
	void switchRevealed();
};

#endif
