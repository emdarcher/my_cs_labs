#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define TEMP_ARR_X 20
#define TEMP_ARR_Y 20

int init_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]);
int print_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]);
void copy_temp_arr(float from_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float to_temps[TEMP_ARR_Y][TEMP_ARR_X]);

float calc_temp_arr(float prev_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float calc_temps[TEMP_ARR_Y][TEMP_ARR_X]);

int main(){
    float old_temps[TEMP_ARR_Y][TEMP_ARR_X];
    float new_temps[TEMP_ARR_Y][TEMP_ARR_X];
    init_temp_arr(new_temps);
    copy_temp_arr(new_temps, old_temps);

    //testing printing
    print_temp_arr(old_temps);
    print_temp_arr(new_temps); 

    return 0;
}

//returns the value of the greatest change
float calc_temp_arr(float prev_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float calc_temps[TEMP_ARR_Y][TEMP_ARR_X]){

}

int init_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]){
    int len_y = TEMP_ARR_Y;
    int len_x = TEMP_ARR_X;
    for(int y=0; y<len_y; y++){
        for(int x=0; x<len_x; x++){
            if((y==0)||(y==(len_y-1))){
                temps[y][x] = ((x==0)||(x==(len_x-1))) ? 0.0 : 100.0;
            } else {
                temps[y][x] = 0.0;
            }
        }
    }
}

void copy_temp_arr(float from_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float to_temps[TEMP_ARR_Y][TEMP_ARR_X]){
    for(int y=0;y<TEMP_ARR_Y;y++){
        for(int x=0;x<TEMP_ARR_X;x++){
            to_temps[y][x] = from_temps[y][x]; 
        }
    }
}

int print_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]){
    int len_y = TEMP_ARR_Y;
    int len_x = TEMP_ARR_X;
    for(int y=0;y<len_y;y++){
        for(int x=0;x<len_x;x++){
            printf("%6.1f", temps[y][x]);
        }
        printf("\n");
    }
}
