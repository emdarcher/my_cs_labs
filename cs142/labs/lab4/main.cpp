#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

#define BUFF_SIZE   16
#define ERRORED     1
#define NO_ERR      0

int get_int(int buffsize, int &in_int);
int get_slot(int &in_slot);
int get_chips(int &in_chips);
int run_menu(void);
int single_chip(void);
int multiple_chips(void);

//NOTE:
//make integer input checking function

int get_int(int buffsize, int &in_int){
    char buf[buffsize];
    int tmp_int;
    fgets( buf, sizeof(buf), stdin ); 
    //check for integer input
    if(sscanf( buf, "%i", &tmp_int ) == 1){
        in_int = tmp_int;
        return NO_ERR;
    }
    return ERRORED;
}

enum {
    SINGLE_CHIP = 1,
    MULTIPLE_CHIPS = 2,
    QUIT_PRGM,
};

int main(){
    int option = 0;    
    int main_loop_var = 1;
    while(main_loop_var){
        option = run_menu();
        int error = 0;
        switch (option) {
            case SINGLE_CHIP:
                error = single_chip();
                break;
            case MULTIPLE_CHIPS:
                error = multiple_chips();
                break;
            case QUIT_PRGM:
                printf("GOODBYE!\n");
                return 0;
                break;
        }
    }
    return 0;
}

#define SLOT_MAX 8
#define SLOT_MIN 0

int run_menu(void){
    char buf[BUFF_SIZE];
    int opt = 0;
    int loop_var = 1;
    while(loop_var){
        printf("MENU: Please select one of the following options:\n"
                "  1 - Drop a single chip into one slot\n"
                "  2 - Drop multiple chips into one slot\n"
                "  3 - Quit the program\n"
                "Enter your selection now: ");
        //int in_ret = scanf(" %i%c", &option, &term);   
        fgets( buf, sizeof(buf), stdin ); 
        //if(!((in_ret != 2) || (term != '\n'))){
        //check for integer input
        if(sscanf( buf, "%i", &opt ) == 1){
            if((opt > 0) && (opt <= 3)){
                break;
            }
        }
        printf("INVALID SELECTION. Please enter 1, 2 or 3\n\n");
    }
    return opt;
}

int get_slot(int &in_slot){
    int slot;
    printf("Which slot do you want to drop the chip in (0-8)? ");
    //check for integer input
    if(get_int(BUFF_SIZE, slot) == NO_ERR){
        if((slot >= SLOT_MIN) && (slot <= SLOT_MAX)){
            //single chip stuff here
            in_slot = slot;
            return NO_ERR;
        }
    }
    printf("INVALID SLOT.\n");
    return ERRORED;
}

int single_chip(void){
    int slot;
    printf("*** DROP SINGLE CHIP ***\n");
    if(get_slot(slot) == NO_ERR){
        return NO_ERR;
    }
    return ERRORED;
}

int get_chips(int &in_chips){

}

int multiple_chips(void){
    int slot, chips;
    printf("*** DROP MULTIPLE CHIPS ***\n");

}

