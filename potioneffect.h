#ifndef POTIONEFFECT_H
#define POTIONEFFECT_H

class PotionEffect {
	int atk, def;
public:
	PotionEffect(int atk, int def);
	~PotionEffect();
	void setAtk(int atk);
	void setDef(int def);
	int getAtk();
	int getDef();
};

#endif
