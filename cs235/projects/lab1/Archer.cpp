#include "Archer.h"


Archer::Archer(string name, int hit_points, int strength,
        int speed, int magic) : Fighter(name, hit_points, strength,
                                    speed, magic){
    this->original_speed = speed; 
}
Archer::~Archer(){}
bool Archer::useAbility(){
    speed += 1;
    return true;
}
void Archer::reset(){
    Fighter::reset();
    speed = original_speed;
}
int Archer::getDamage(){
    return this->speed;
}
