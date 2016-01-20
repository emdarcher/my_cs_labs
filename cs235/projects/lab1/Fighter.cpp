
#include "Fighter.h"

Fighter::Fighter(string name, int hit_points, int strength,
        int speed, int magic){
    this->name = name;
    this->hit_points = hit_points;
    this->max_hit_points = hit_points;

    this->strength = strength;
    this->speed = speed;
    this->magic = magic;
    
}

Fighter::~Fighter(){}

string Fighter::getName(){
    return this->name;
}

int Fighter::getMaximumHP(){
    return this->max_hit_points;
}

int Fighter::getCurrentHP(){
    return this->hit_points;
}

int Fighter::getStrength(){
    return this->strength;
}

int Fighter::getSpeed(){
    return this->speed;
}

int Fighter::getMagic(){
    return this->magic;
}

void Fighter::takeDamage(int damage){
    damage = damage - (this->speed / 4);
    damage = (damage<1) ? 1 : damage;
    this->hit_points -= damage; 
}

void Fighter::reset(){
    this->hit_points = this->max_hit_points;
}

void Fighter::regenerate(){
    regen_amount = (this->strength / 6);
    if(regen_amount < 1){
        regen_amount = 1;
    }
    this->hit_points += regen_amount;
    if(this->hit_points > this->max_hit_points){
        this->hit_points = this->max_hit_points; 
    }
}

