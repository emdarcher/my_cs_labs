/*
 *  TEST CASES and Notes:
 * 
 *
 */


//#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//using namespace std;

#define BUFF_SIZE   16
#define ERRORED     1
#define NO_ERR      0

#define SLOT_MIN    0
#define SLOT_MAX    8

#define OPT_MIN     1
#define OPT_MAX     3   

#define PEG_ROWS    12

const int final_slot_vals[] = {
    100,500,1000,0,10000,0,1000,500,100
};

//function prototypes
int get_int(int buffsize, int *in_int);
int get_slot(int *in_slot);
int get_chips(int *in_chips);
int run_menu(void);
int single_chip(void);
int multiple_chips(void);
int all_slots_multiple_chips(void);
float get_winnings(int slot); 

uint8_t get_rand_bool(void);
int single_chip_path(int slot, float * path_arr);
int multiple_chips_calc(int chips, int slot);

int get_int(int buffsize, int *in_int){
    char buf[buffsize];
    int tmp_int;
    char end_char;
    fgets( buf, sizeof(buf), stdin ); 
    //check for integer input
    if(sscanf( buf, "%i%c", &tmp_int, &end_char ) == 2){
        //check if integer is followed by a newline
        if(end_char == '\n'){
            *in_int = tmp_int;
            return NO_ERR;
        }
    }
    return ERRORED;
}

enum {
    SINGLE_CHIP = 1,
    MULTIPLE_CHIPS = 2,
    ALL_SLOTS_MULTIPLE_CHIPS,
    QUIT_PRGM,
};

int main(){
    int option = 0;    
    int main_loop_var = 1;
    //seed the random number generator
    srand(time(0));
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
            case ALL_SLOTS_MULTIPLE_CHIPS:  
                error = all_slots_multiple_chips();
                break;
            case QUIT_PRGM:
                printf("GOODBYE!\n");
                return 0;
                break;
        }
    }
    return 0;
}


uint8_t rand_bool(void){
    unsigned int in_rand = rand();
    return (in_rand & 0x01);
}

int single_chip_path(int slot, float * path_arr){
    float f_slot = (float)(slot * 1.0);
    path_arr[0] = f_slot;
    float pos   = f_slot;
    int  final_row;
    for(int r=1;r<=PEG_ROWS;r++){
        if((pos > SLOT_MIN) && (pos < SLOT_MAX)){
            pos += (rand_bool()) ? -0.5 : 0.5;
        } else {
            pos += (pos==SLOT_MIN) ? 0.5 : -0.5;
        }
        path_arr[r] = pos;
        final_row = r;        
    }
    int final_pos = (int)path_arr[final_row];
    return final_pos; 
}

int run_menu(void){
    int opt = 0;
    int loop_var = 1;
    while(loop_var){
        printf("MENU: Please select one of the following options:\n"
                "  1 - Drop a single chip into one slot\n"
                "  2 - Drop multiple chips into one slot\n"
                "  3 - Quit the program\n"
                "Enter your selection now: ");
        //check for integer input
        if(get_int(BUFF_SIZE, &opt) == NO_ERR){
            if((opt >= OPT_MIN) && (opt <= OPT_MAX)){
                break;
            }
        }
        printf("INVALID SELECTION. Please enter 1, 2 or 3\n\n");
    }
    return opt;
}

int get_slot(int *in_slot){
    int slot;
    printf("Which slot do you want to drop the chip in (0-8)? ");
    //check for integer input
    if(get_int(BUFF_SIZE, &slot) == NO_ERR){
        if((slot >= SLOT_MIN) && (slot <= SLOT_MAX)){
            //single chip stuff here
            *in_slot = slot;
            return NO_ERR;
        }
    }
    printf("INVALID SLOT.\n\n");
    return ERRORED;
}

int single_chip(void){
    int slot, final_slot;
    float path[PEG_ROWS+1];
    printf("\n*** DROP SINGLE CHIP ***\n");
    if(get_slot(&slot) == NO_ERR){
        final_slot = single_chip_path(slot, path); 
        printf("\n*** DROPPING CHIP INTO SLOT %i ***\n", slot);
        printf("PATH: [");
        for(int r=0;r<=PEG_ROWS;r++){
            printf("%3.1f%c", path[r], ((r<PEG_ROWS)? ' ':']')); 
        }
        printf("\nWINNINGS: $%.2f\n\n", (float)final_slot_vals[final_slot]); 
        return NO_ERR;
    }
    return ERRORED;
}

int get_chips(int *in_chips){
    int chips;
    printf("How many chips do you want to drop (>0)? ");
    if(get_int(BUFF_SIZE, &chips) == NO_ERR){
        if(chips > 0){
            *in_chips = chips;
            return NO_ERR;
        }
    }
    printf("INVALID NUMBER OF CHIPS.\n\n");
    return ERRORED;
}

int all_slots_multiple_chips(void){

}
float get_winnings(int slot){
    return (float)final_slot_vals[slot];
}
int multiple_chips_calc(int chips, int slot){
    
}

int multiple_chips(void){
    int slot, chips;
    float total_winnings = 0.0, avg_winnings = 0.0;
    float path[PEG_ROWS+1];
    printf("*** DROP MULTIPLE CHIPS ***\n");
    if(get_chips(&chips) == NO_ERR){
        if(get_slot(&slot) == NO_ERR){
            for(int c=0;c<chips;c++){
                int final_slot = single_chip_path(slot, path);
                total_winnings += (float)final_slot_vals[final_slot]; 
            }
            printf("Total Winnings on %i chips: $%.2f\n", 
                    chips, total_winnings);
            avg_winnings = (float)(total_winnings / chips);
            printf("Average winnings per chip: $%.2f\n\n", avg_winnings); 
            return NO_ERR;
        }
    }
    return ERRORED;
}

