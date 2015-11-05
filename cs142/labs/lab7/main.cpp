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

#define NOT_FOUND   -1

int get_int(int *in_int);
int run_menu(void);
void print_restaurants(vector<string> restaurants);

int find_restaurant(char * name_str, vector<string> restaurants);

int add_restaurant(vector<string>& restaurants);

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

    int option = 0;    
    uint8_t main_loop_var = 1;
    while(main_loop_var){
        option = run_menu();
        int error = 0;
        //handle the different option cases
        switch (option) {
            case ADD_A_RESTAURANT:
                error = add_restaurant(restaurants);
                break;
            case DISPLAY_ALL_RESTAURANTS:
                print_restaurants(restaurants);
                break;
            case QUIT_THE_PROGRAM:
                //printf("GOODBYE!\n");
                return 0;
                break;
        }
    }
    return 0;
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
    scanf("%s",name_buff);
    int index = find_restaurant(name_buff, restaurants);
    if(index == NOT_FOUND){
        printf("No name conflict found, adding \"%s\" to the vector.\n", 
                name_buff);
        //constructing string object using char array string
        string name_str(name_buff);
        restaurants.push_back(name_str);
        return NO_ERR;
    } else {
        printf("Name conflict found! Will not add \"%s\" to the vector.\n",
               name_buff); 
        return ERRORED;
    }
}

void print_restaurants(vector<string> restaurants){
    for(int i=0;i<restaurants.size();i++){
        printf("%s", restaurants[i].c_str());
        if(i != restaurants.size() - 1){
            printf(", ");
        }
    }
    printf("\n");
}
