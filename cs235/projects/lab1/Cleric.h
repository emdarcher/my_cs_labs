#include "Fighter.h"

#ifndef CLERIC_H
#define CLERIC_H


class Cleric : public Fighter {
    private:
        int mana;
        int max_mana;

    public:
        Cleric(string name, int hit_points, int strength,
                int speed, int magic);
        ~Cleric();
		virtual void regenerate();
		virtual bool useAbility();
        virtual void reset();
        virtual int getDamage();

};

#endif
