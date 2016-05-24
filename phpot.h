#ifndef PHPOT_H
#define PHPOT_H
#include "potion.h"

class Game;

class PHPot:public Potion{
	
public:
	static bool revealed;
	PHPot(Game *game);
	void pickedUp();
	bool isRevealed();
	void switchRevealed();
};

#endif
