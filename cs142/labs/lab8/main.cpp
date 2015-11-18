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


//function prototypes
int run_menu(void);


int main(){

    return 0;
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
