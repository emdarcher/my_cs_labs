//
//
//this has to be defined for this to compile in Visual Studio
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include "Car.h"

using namespace std;

//constants
#define OPT_MIN     1
#define OPT_MAX     8

#define INIT_CASH_BALANCE   10000.00

#define INPUT_BUFF_SIZE     128

#define NO_ERR  0
#define ERRORED 1


//function prototypes
int run_menu(void);
int get_int(int *in_int);
int get_double(double *in_double);
int get_word(char * word);
void show_inv(vector<Car*> inv);
void show_bal(double bal);
int buy_car(vector<Car*> *inv, double * bal);

uint8_t car_exists(vector<Car*> inv, char * name);

enum {
    SHOW_CURR_INV = OPT_MIN,
    SHOW_CURR_BAL,
    BUY_A_CAR,
    SELL_A_CAR,
    PAINT_A_CAR,
    LOAD_FILE,
    SAVE_FILE,
    QUIT_PROGRAM
};

int main(){
    vector<Car*> inventory;    
    double balance = INIT_CASH_BALANCE;
    int option = 1;
    uint8_t main_loop_var = 1;
    while(main_loop_var){
        option = run_menu();      
        int error = 0;
        //handle the options
        switch(option){
            case SHOW_CURR_INV:
                show_inv(inventory);
                break;
            case SHOW_CURR_BAL:
                show_bal(balance);
                break;
            case BUY_A_CAR:
                error = buy_car(&inventory, &balance);
                break;
            case SELL_A_CAR:
                break;
            case PAINT_A_CAR:
                break;
            case LOAD_FILE:
                break;
            case SAVE_FILE:
                break;
            case QUIT_PROGRAM:
                printf("QUITTING THE PROGRAM!\n");
                return 0;
                break;     
        }
    }  
    return 0;
}

void show_inv(vector<Car*> inv){
    printf("Inventory: \n");
    for(int i=0;i<(inv.size());i++){
        string car_str = (*inv[i]).toString();
        printf("%s", car_str.c_str());
    } 
}

void show_bal(double bal){
    printf("Current Balance: $%0.2lf\n", bal);
}

uint8_t car_exists(vector<Car*> inv, char * name){
    for(int i=0;i<inv.size();i++){
        string car_name = (*inv[i]).getName();
        if(!strcmp(name, car_name.c_str())){
            return 1;
        }
    }
    return 0;
}

int buy_car(vector<Car*> *inv, double * bal){
    char name[INPUT_BUFF_SIZE];
    printf("Enter name of the Car: ");
    //scanf("%s", name);
    get_word(name);
    //if(get_word(name) == ERRORED){
    //    printf("INVALID INPUT!\n");
    //    return ERRORED;
    //}
    if(car_exists(*inv, name)){
        printf("Car with name %s already exists!\n", name);
        return ERRORED;
    } 
    printf("Enter the color of the Car: ");
    char color[INPUT_BUFF_SIZE];
    get_word(color);
    //scanf("%s", color);
    //getchar();
    double price = 0;    
    printf("Enter the price of the Car: ");
    //check for double input
    if(get_double(&price) == NO_ERR){
        if(price > *bal){
            printf("The price %0.2lf is greater than the balance of %0.2lf!\n",
                    price, *bal);
            return ERRORED;
        } 
        //subtract price from balance
        *bal -= price;
        string name_string(name);
        string color_string(color);
        Car* tmp_Car_ptr = new Car(name_string, color_string, price);
        (*inv).push_back(tmp_Car_ptr);
        printf("Just added car with these details:\n%s",
                (*tmp_Car_ptr).toString().c_str());
        return NO_ERR;
    } else {
        printf("INVALID INPUT!\n");
        return ERRORED;
    }

}

int get_word(char * word){
    char buf[INPUT_BUFF_SIZE];
    char tmp_word[INPUT_BUFF_SIZE];
    
    fgets( buf, sizeof(buf), stdin);

    if(sscanf(buf, "%s", tmp_word) == 1){
        strcpy(word, tmp_word);
        return NO_ERR;
    }
    return ERRORED;
}

int get_double(double *in_double){
    char buf[INPUT_BUFF_SIZE];
    double tmp_double;
    char end_char;
    fgets( buf, sizeof(buf), stdin ); 
    //check for double input and ending character
    if(sscanf( buf, "%lf%c", &tmp_double, &end_char ) == 2){
        //check if double is followed by a newline character
        if(end_char == '\n'){
            *in_double = tmp_double;
            return NO_ERR;
        }
    }
    return ERRORED;
}

int get_int(int *in_int){
    char buf[INPUT_BUFF_SIZE];
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
    //run the base menu
    int opt = 0;
    int loop_var = 1;
    while(loop_var){
        printf("MENU: Please select one of the following options:\n"
                "  1 - Show Current Inventory\n"
                "  2 - Show Current Balance\n"
                "  3 - Buy a Car\n"
                "  4 - Sell a Car\n"
                "  5 - Paint a Car\n"
                "  6 - Load File\n"
                "  7 - Save File\n"
                "  8 - Quit Program\n"
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
