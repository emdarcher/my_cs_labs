#ifndef ARENA_H
#define ARENA_H


#include "ArenaInterface.h"
#include "Fighter.h"
#include "Cleric.h"
#include "Archer.h"
#include "Robot.h"

#define NAME_BUFF 64

class Arena : public ArenaInterface {
    private:

        vector<FighterInterface*> fighters;
        void string_to_stats(string in_str, string * name, char * type,
                int * max_hit_points, int * strength, int * speed, int * magic);
    public:
        Arena();
        ~Arena();

        virtual bool addFighter(string info);
        virtual bool removeFighter(string name);
        virtual FighterInterface* getFighter(string name);
        virtual int getSize(); 

};

#endif
