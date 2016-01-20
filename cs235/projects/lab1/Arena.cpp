#include "Arena.h"
#include <string.h>

Arena::Arena(){
         
}

Arena::~Arena(){}

void string_to_stats(string in_str, string * name, char * type,
        int * max_hit_points, int * strength, int * speed, int * magic){
   
    char name_str[NAME_BUFF];

    sscanf(in_str.c_str(), "%s %c %i %i %i %i", name_str, type,
           max_hit_points, strength, speed, magic);

    *name = string(name_str); 

}

bool Arena::addFighter(string info){
     
}

bool Arena::removeFighter(string name){

}

FighterInterface* Arena::getFighter(string name){

}

int Arena::getSize(void){

}

