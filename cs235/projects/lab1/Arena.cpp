#include "Arena.h"
#include <string.h>

Arena::Arena(){
         
}

Arena::~Arena(){}


/*  string_to_stats(...)
 *
 *  takes in a string to parse into stats for a new fighter
 *
 *  returns NO_ERR (0) if it parses correctly, else it
 *  returns ERRORED (1) if it fails to parse correctly
 *
 */
int Arena::string_to_stats(string in_str, string * name, char * type,
        int * max_hit_points, int * strength, int * speed, int * magic){
   
    char name_str[NAME_BUFF];

    if(sscanf(in_str.c_str(), "%s %c %i %i %i %i", name_str, type,
           max_hit_points, strength, speed, magic) == 6){

        *name = string(name_str); 
        return NO_ERR; 
    }
    return ERRORED;

}


/*
 *  find_fighter(string)
 *
 *  locates a fighter with the given name string in the fighters vector
 *  if it finds a match, it returns the index in the vector where it
 *  is located, and if not it returns DOES_NOT_EXIST (-1).
 */
int Arena::find_fighter(string name){
    for(int i=0;i<fighters.size();i++){
        if( (*fighters[i]).getName() == name ){
            return i;
        } 
    } 
    return DOES_NOT_EXIST;
} 

		/*
		 *	addFighter(string)
		 *
		 *	Adds a new fighter to the collection of fighters in the arena. Do not allow 
		 *	duplicate names.  Reject any string that does not adhere to the format 
		 *	outlined in the lab specs.
		 *
		 *	Return true if a new fighter was added; false otherwise.
		 */
bool Arena::addFighter(string info){
    string name;
    char type;
    int max_hit_points, strength, speed, magic;
    if(string_to_stats(info, &name, &type, &max_hit_points, 
                            &strength, &speed, &magic) == NO_ERR){
      
        if(find_fighter(name) == DOES_NOT_EXIST){
            Fighter* tmp_Fighter_ptr; 
            if(type == TYPE_ROBOT){
                tmp_Fighter_ptr = new Robot(name, max_hit_points, 
                                            strength, speed, magic);
            } else if(type == TYPE_ARCHER){
                tmp_Fighter_ptr = new Archer(name, max_hit_points, 
                                            strength, speed, magic);
            } else if(type == TYPE_CLERIC){
                tmp_Fighter_ptr = new Cleric(name, max_hit_points, 
                                            strength, speed, magic);
            } else {
                return false;
            }

            fighters.push_back(tmp_Fighter_ptr);  
            return true;
        }
    }   

    return false;  
}

		/*
		 *	removeFighter(string)
		 *
		 *	Removes the fighter whose name is equal to the given name.  Does nothing if 
		 *	no fighter is found with the given name.
		 *
		 *	Return true if a fighter is removed; false otherwise.
		 */
bool Arena::removeFighter(string name){
    int fighter_index = find_fighter(name);
    if(fighter_index != DOES_NOT_EXIST){
        FighterInterface* tmp_FighterI_ptr = fighters[fighter_index];
        //deallocate memory
        delete tmp_FighterI_ptr;
        //erase pointer from the vector
        fighters.erase(fighters.begin() + fighter_index);
        return true;
    } 
    return false;
}

		/*
		 *	getFighter(string)
		 *
		 *	Returns the memory address of a fighter whose name is equal to the given 
		 *	name.  Returns NULL if no fighter is found with the given name.
		 *
		 *	Return a memory address if a fighter is found; NULL otherwise.
		 */
FighterInterface* Arena::getFighter(string name){
    int fighter_index = find_fighter(name);
    if(fighter_index != DOES_NOT_EXIST){
        return fighters[fighter_index];
    }
    return NULL;
}

		/*
		 *	getSize()
		 *
		 *	Returns the number of fighters in the arena.
		 *
		 *	Return a non-negative integer.
		 */
int Arena::getSize(){
    return fighters.size();
}

