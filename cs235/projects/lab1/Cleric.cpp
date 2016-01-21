#include "Cleric.h"


Cleric::Cleric(string name, int hit_points, int strength,
        int speed, int magic) : Fighter(name, hit_points, strength,
                                    speed, magic){
    this->max_mana = magic*5;
    this->mana = this->max_mana;


}
Cleric::~Cleric(){}
void Cleric::regenerate(){
    Fighter::regenerate();
    int mana_inc = magic/5;
    if(mana_inc < 1){
        mana_inc = 1;
    }
    mana += mana_inc;
    if(mana > max_mana){
        mana = max_mana;
    }
}
bool Cleric::useAbility(){
    
    if(mana >= CLERIC_ABILITY_COST){
        int hit_points_inc = magic/3;
        if(hit_points_inc < 1){
            hit_points_inc = 1;
        }  
        hit_points += hit_points_inc;
        if(hit_points > max_hit_points){
            hit_points = max_hit_points;   
        }
        mana -= CLERIC_ABILITY_COST;
        return true;
    }
    return false;
}
void Cleric::reset(){
    Fighter::reset();
    this->mana = this->max_mana;
}
int Cleric::getDamage(){
    return this->magic;
}
