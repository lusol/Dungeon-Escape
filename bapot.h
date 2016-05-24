
#ifndef BAPOT_H
#define BAPOT_H
#include "potion.h"

class Game;

class BAPot:public Potion{
public:
	static bool revealed;
	BAPot(Game *game);
	void pickedUp();
	bool isRevealed();
	void switchRevealed();
};

#endif
