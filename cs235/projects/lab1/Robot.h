#include "Fighter.h"

#ifndef ROBOT_H
#define ROBOT_H

class Robot : public Fighter {
   
    private:
        int energy;
        int max_energy;
        int bonus_damage;

    public:
        Robot(string name, int hit_points, int strength,
                int speed, int magic);
        ~Robot();
        virtual int getDamage();
        virtual void reset();
		virtual bool useAbility();

};

#endif
