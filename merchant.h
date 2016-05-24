#ifndef MERCHANT_H
#define MERCHANT_H

class Game;
class Player;

class Merchant : public Enemy{
public:
	static bool aggressive;
    Merchant(Game *game);
    void Attack(Player *player);
    bool getAggressive();
    void switchAggressive();
};

#endif
