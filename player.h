#ifndef PLAYER_H
#define PLAYER_H
#include "object.h"
#include "potioneffect.h"
#include <iostream>

class Enemy;

class Player : public Object {
protected:
      int atk;
      int def;
      int gold;
      int hp;
      int maxHP;
      PotionEffect *pe;
      std::string checkSurroundingPots();
public:
      virtual ~Player() = 0;
      int getAtk();
      int getDef();
      int getHP();
      int getMaxHP();
      int getGold();
      void setMaxHP(int hp);
      void setHP(int newhp);
      void setGold(int gold);
      static Player* PlayerFactory(char race, Game *game);
      virtual void Attack(std::string direction) = 0;
      PotionEffect* getPotionEffect();
      bool Defend(Enemy *enemy);
      void Move(std::string direction);
      void Use(std::string direction);
      void atkEnemy(Enemy* enemy);
};


#endif
