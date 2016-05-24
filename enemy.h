#ifndef ENEMY_H
#define ENEMY_H
#include "game.h"

class Player;

class Enemy : public Object {
	protected:
		int hp,atk,def;
	public:
		int getAtk();
		int getDef();
		bool isDead();
		void setHP(int hp);
		int getHP();
		void atkPlayer(Player *player);
		bool Defend(Player *player);
		void Move();
		virtual void Attack(Player *player) = 0;
		virtual ~Enemy() = 0;
};

#endif
