
#ifndef FIGHTER_H
#define FIGHTER_H

#include "FighterInterface.h"

class Fighter : public FighterInterface {
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

        virtual string getName() const;
        virtual int getMaximumHP() const;
        virtual int getCurrentHP() const;
        virtual int getStrength() const;
		virtual int getSpeed() const;
		virtual int getMagic() const;
		virtual int getDamage() = 0;
		virtual void takeDamage(int damage);
		virtual void reset();
		virtual void regenerate();
		virtual bool useAbility() = 0;


};

#endif
