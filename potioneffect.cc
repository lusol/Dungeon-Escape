#include "potioneffect.h"

//sets atk and def
PotionEffect::PotionEffect(int atk, int def){
	this->atk = atk;
	this->def = def;
}

//destructor
PotionEffect::~PotionEffect(){}

//set atk to indicated value. If value is less than 0,
//set atk to 0
void PotionEffect::setAtk(int atk){
	if(atk<0){
		this->atk = 0;
	}
	else{
	this->atk = atk;
	}
}

//set def to indicated value. If value is less than 0, set
//def to 0
void PotionEffect::setDef(int def){
if(def<0){
	this->def = 0;
}
else{
	this->def = def;
}
}
//return atk
int PotionEffect::getAtk(){return atk;}

//return def
int PotionEffect::getDef(){return def;}
