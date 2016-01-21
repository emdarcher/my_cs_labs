#include "Robot.h"
#include <cmath>

Robot::Robot(string name, int hit_points, int strength,
        int speed, int magic) : Fighter(name, hit_points, strength,
                                    speed, magic){
    this->max_energy = this->magic * 2;
    this->energy = this->max_energy;
    this->bonus_damage = 0;

}
Robot::~Robot(){}
int Robot::getDamage(){
    int damage;
    if(bonus_damage > 0){
        damage = strength + bonus_damage;
        bonus_damage = 0;
    } else {
        damage = strength;
    }
    return damage;
}
void Robot::reset(){
    Fighter::reset();
    this->energy = this->max_energy;
    this->bonus_damage = 0;
}
bool Robot::useAbility(){
    //runs the shockwave punch
    //
    if(energy >= ROBOT_ABILITY_COST){
        this->bonus_damage = ((double)strength * 
                        pow(((double)energy/(double)max_energy),4.0));

        //subtract the energy
        energy -= ROBOT_ABILITY_COST;
        return true;
    }
    return false;
}
