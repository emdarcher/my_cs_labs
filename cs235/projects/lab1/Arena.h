#ifndef ARENA_H
#define ARENA_H


#include "ArenaInterface.h"


class Arena : public ArenaInterface {
    private:
        vector<FighterInterface*> fighters;
    public:
        Arena(){}
        ~Arena(){}

        virtual bool addFighter(string info) const;
        virtual bool removeFighter(string name) const;
        virtual FighterInterface* getFighter(string name);
        virtual int getSize(void) const; 


};

#endif
