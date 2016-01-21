
#ifndef FIGHTER_H
#define FIGHTER_H

#include "FighterInterface.h"

class Fighter : virtual public FighterInterface {
    protected:
        string name;
        int hit_points;
        int max_hit_points;
        int strength;
        int speed;
        int magic;
        int damage; 
    public:
        Fighter(string name, int hit_points, int strength,
                int speed, int magic);
        virtual ~Fighter();

        virtual string getName();
        virtual int getMaximumHP();
        virtual int getCurrentHP();
        virtual int getStrength();
		virtual int getSpeed();
		virtual int getMagic();
		virtual int getDamage() = 0;
		virtual void takeDamage(int damage);
		virtual void reset();
		virtual void regenerate();
		virtual bool useAbility() = 0;


};

#endif
