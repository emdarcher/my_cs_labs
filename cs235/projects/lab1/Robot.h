#include "Fighter.h"

class Robot : public Fighter {
   
    private:
        int energy;

    public:
        virtual int getDamage() const;
        virtual void reset();
		virtual bool useAbility() const;

};
