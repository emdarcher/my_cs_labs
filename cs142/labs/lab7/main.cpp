#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>

using namespace std;

#define BUFF_SIZE   128

#define ERRORED     1
#define NO_ERR      0

#define OPT_MIN     1
#define OPT_MAX     6

#define CHOICE1     1
#define CHOICE2     2

#define NOT_FOUND   -1

#define MAX_SWAPS_MULTIPLIER    3

int get_int(int *in_int);
int run_menu(void);
void print_restaurants(vector<string> restaurants);

int find_restaurant(char * name_str, vector<string> restaurants);

int add_restaurant(vector<string>& restaurants);
int remove_restaurant(vector<string>& restaurants);

void shuffle_restaurants(vector<string>& restaurants);

int run_tournament(vector<string>& restaurants);

int powerOfTwo(unsigned int in_val){
    //checks for zero then
    //check if there is only one bit in the variable
    //(which means it's a power of two because in the binary system
    //each bit is a power of two)
    //it checks by using binary AND '&'
    //example 
    //64 == 0b01000000
    //64 - 1 == 63 == 0b00111111
    //64 & 63 == 0b01000000 & 0b00111111 == 0b00000000 == 0
    //so therefore 64 is a power of 2
    return ((in_val != 0) && !(in_val & (in_val - 1)));
}

#define INIT_RESTAURANT_NUM 8 
void init_restaurants(vector<string>& restaurants){ 
    string rest[] = {
        "Five Guys",
        "SubWay",
        "Chick-Fil-A",
        "In-n-Out",
        "Wagamama",
        "Taco Bell",
        "KFC",
        "Olive Garden"
    };
    for(int i=0;i<INIT_RESTAURANT_NUM;i++){
        restaurants.push_back(rest[i]); 
    }
}

enum {
    DISPLAY_ALL_RESTAURANTS = 1,
    ADD_A_RESTAURANT,
    REMOVE_A_RESTAURANT,
    SHUFFLE_THE_VECTOR,
    BEGIN_THE_TOURNAMENT,
    QUIT_THE_PROGRAM
};

int main(){
    vector<string> restaurants;
    init_restaurants(restaurants);
    srand(time(0));
    int option = 0;    
    uint8_t main_loop_var = 1;
    while(main_loop_var){
        option = run_menu();
        int error = 0;
        //handle the different option cases
        switch (option) {
            case DISPLAY_ALL_RESTAURANTS:
                print_restaurants(restaurants);
                break;
            case ADD_A_RESTAURANT:
                error = add_restaurant(restaurants);
                break;
            case REMOVE_A_RESTAURANT:
                error = remove_restaurant(restaurants);
                break;
            case SHUFFLE_THE_VECTOR:
                shuffle_restaurants(restaurants);
                break;
            case BEGIN_THE_TOURNAMENT:
                error = run_tournament(restaurants);
                if(error == NO_ERR){
                    return 0;
                }
                break;
            case QUIT_THE_PROGRAM:
                //printf("GOODBYE!\n");
                return 0;
                break;
        }
    }
    return 0;
}


int run_tournament(vector<string>& restaurants){
    unsigned int r_size = restaurants.size();
    if(!powerOfTwo(r_size)){
        printf("The amount of restaurants is not a power of two, "
                "so tournament cannot start.\n");
        return ERRORED;
    }
    int rounds = 0;
    unsigned int tmp_size = r_size;
    //finds power of two by bit shifting until zero
    while((tmp_size >>= 1)){
        rounds++;        
    }

    printf("starting with %i rounds.\n", rounds);
    for(int r=1;r<=rounds;r++){
        //get the amount of matches
        int matches = (r_size >> r);
        for(int m=1;m<=matches;m++){
            int opt = 0;
            uint8_t loop_var = 1;
            char * name1 = restaurants[m-1].c_str();
            char * name2 = restaurants[m].c_str();
            while(loop_var){
                printf("Match %i/%i, Round %i/%i --- 1: %s or 2: %s? ",
                        m, matches, r, rounds, name1, name2); 
                //check for integer input
                if(get_int( &opt) == NO_ERR){
                    if((opt == CHOICE1) || (opt == CHOICE2)){
                        break;
                    }
                }
                printf("Invalid response. Please enter %i or %i\n",
                        CHOICE1, CHOICE2);
            }

        }
    } 

}

int get_int(int *in_int){
    char buf[BUFF_SIZE];
    int tmp_int;
    char end_char;
    fgets( buf, sizeof(buf), stdin ); 
    //check for integer input and ending character
    if(sscanf( buf, "%i%c", &tmp_int, &end_char ) == 2){
        //check if integer is followed by a newline character
        if(end_char == '\n'){
            *in_int = tmp_int;
            return NO_ERR;
        }
    }
    return ERRORED;
}

int run_menu(void){

    int opt = 0;
    int loop_var = 1;
    while(loop_var){
        printf("MENU: Please select one of the following options:\n"
                "  1 - Display all restaurants\n"
                "  2 - Add a restaurant\n"
                "  3 - Remove a restaurant\n"
                "  4 - Shuffle the vector\n"
                "  5 - Begin the tournament\n"
                "  6 - Quit the program\n"
                "Enter your selection now: ");
        //check for integer input
        if(get_int( &opt) == NO_ERR){
            if((opt >= OPT_MIN) && (opt <= OPT_MAX)){
                break;
            }
        }
        printf("INVALID SELECTION. Please enter an int between %i and %i\n\n",
                    OPT_MIN, OPT_MAX);
    }
    return opt;

}

int find_restaurant(char * name_str, vector<string> restaurants){
    for(int i=0;i<restaurants.size();i++){
        if(!strcmp(name_str,restaurants[i].c_str())){
            return i;
        } 
    }
    return NOT_FOUND;
}

int add_restaurant(vector<string>& restaurants){
    char name_buff[BUFF_SIZE];
    printf("Enter the name of the restaurant you want to add: ");
    //get a line of input and copy into the buffer.
    fgets(name_buff, BUFF_SIZE, stdin);
    int index = find_restaurant(name_buff, restaurants);
    if(index == NOT_FOUND){
        printf("No name conflict found, adding \"%s\" to the vector.\n\n", 
                name_buff);
        //constructing string object using char array string
        string name_str(name_buff);
        restaurants.push_back(name_str);
        return NO_ERR;
    } else {
        printf("Name conflict found! Will not add \"%s\" to the vector.\n\n",
               name_buff); 
        return ERRORED;
    }
}

int remove_restaurant(vector<string>& restaurants){
    char name_buff[BUFF_SIZE];
    printf("Enter the name of the restaurant you want to remove: ");
    //get a line of input and copy into the buffer.
    fgets(name_buff, BUFF_SIZE, stdin);
    int index = find_restaurant(name_buff, restaurants);
    if(index == NOT_FOUND){
        printf("No restaurant with name \"%s\" found. Not removing.\n\n", 
                name_buff);
        return ERRORED;
    } else {
        printf("Restaurant with name \"%s\" found. "
                "Removing from the vector.\n\n",
               name_buff); 
        //removing procedure
        //shifting values from the index onwards, then removing the last one.
        for(int i=index;i<(restaurants.size()-1);i++){
            restaurants[i] = restaurants[i+1];
        }
        restaurants.pop_back();

        return NO_ERR;
    }
}

void shuffle_restaurants(vector<string>& restaurants){
    int r_size = restaurants.size();
    int max_swaps = MAX_SWAPS_MULTIPLIER * r_size; 
    for(int i=0;i<max_swaps;i++){
        int index1 = rand() % r_size;
        string tmp_r = restaurants[index1];
        int index2 = rand() % r_size;
        restaurants[index1] = restaurants[index2];
        restaurants[index2] = tmp_r;
    }
    printf("The restaurants have been shuffled.\n\n");
}

void print_restaurants(vector<string> restaurants){
    printf("{");
    for(int i=0;i<restaurants.size();i++){
        printf("%s", restaurants[i].c_str());
        if(i != restaurants.size() - 1){
            printf(", ");
        }
    }
    printf("}\n");
}
