#include "Fighter.h"

class Cleric : public Fighter {
    private:
        int mana;

    public:
		virtual void regenerate();
		virtual bool useAbility() const;
        virtual void reset();
        virtual int getDamage() const;

};
