#include "Fighter.h"

class Archer : public Fighter {

    private:

    public:
		virtual bool useAbility() const;
        virtual void reset();
        virtual int getDamage() const;


};
