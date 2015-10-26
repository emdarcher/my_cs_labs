#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
#define TEMP_ARR_X 20
#define TEMP_ARR_Y 20

float old_temps[TEMP_ARR_Y][TEMP_ARR_X];
float new_temps[TEMP_ARR_Y][TEMP_ARR_X];

int init_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]);
int print_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]);

int main(){
    init_temp_arr(old_temps);
    init_temp_arr(new_temps);
    print_temp_arr(new_temps); 
    return 0;
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
