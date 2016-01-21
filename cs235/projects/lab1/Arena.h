#ifndef ARENA_H
#define ARENA_H


#include "ArenaInterface.h"
#include "Fighter.h"
#include "Cleric.h"
#include "Archer.h"
#include "Robot.h"

#define NAME_BUFF 64

#define DOES_NOT_EXIST -1

#define NO_ERR 0
#define ERRORED 1

const char TYPE_ROBOT = 'R';
const char TYPE_ARCHER = 'A';
const char TYPE_CLERIC = 'C';

class Arena : public ArenaInterface {
    private:

        vector<FighterInterface*> fighters;
        int string_to_stats(string in_str, string * name, char * type,
                int * max_hit_points, int * strength, int * speed, int * magic);
        int find_fighter(string name); 
    public:
        Arena();
        ~Arena();

        virtual bool addFighter(string info);
        virtual bool removeFighter(string name);
        virtual FighterInterface* getFighter(string name);
        virtual int getSize(); 

};

#endif
