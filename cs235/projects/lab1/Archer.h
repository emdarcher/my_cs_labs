#include "Fighter.h"

#ifndef ARCHER_H
#define ARCHER_H

class Archer : public Fighter {

    private:
        int original_speed;
    public:
        Archer(string name, int hit_points, int strength,
                int speed, int magic);
        ~Archer();
		virtual bool useAbility();
        virtual void reset();
        virtual int getDamage();


};

#endif
