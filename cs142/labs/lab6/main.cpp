#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

#define TEMP_ARR_X 20
#define TEMP_ARR_Y 20

#define TEMP_THRESHOLD 0.1

const char csv_file_name[] = "lab6output.csv";

void init_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]);
void print_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]);
void copy_temp_arr(float from_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float to_temps[TEMP_ARR_Y][TEMP_ARR_X]);

float calc_temp_arr(float prev_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float calc_temps[TEMP_ARR_Y][TEMP_ARR_X]);

void export_csv(float temps[TEMP_ARR_Y][TEMP_ARR_X], const char file_name[]);

int main(){
    float old_temps[TEMP_ARR_Y][TEMP_ARR_X];
    float new_temps[TEMP_ARR_Y][TEMP_ARR_X];
    init_temp_arr(new_temps);
    copy_temp_arr(new_temps, old_temps);
    //testing printing
    //print_temp_arr(old_temps);
    //print_temp_arr(new_temps); 
    
    uint8_t first_loop = 1;
    uint8_t loop_var = 1;
    while(loop_var){
        float change;
        change = calc_temp_arr(old_temps, new_temps);
        if(change < TEMP_THRESHOLD){ break; }
        if(first_loop){ 
            print_temp_arr(new_temps); 
            first_loop = 0;
        }
        copy_temp_arr(new_temps, old_temps);
    } 
    export_csv(new_temps, csv_file_name);

    return 0;
}

//returns the value of the greatest change
float calc_temp_arr(float prev_temps[TEMP_ARR_Y][TEMP_ARR_X],
                    float calc_temps[TEMP_ARR_Y][TEMP_ARR_X]){
    float current_change, greatest_change;
    float neighbor_avg;
    for(int y=1;y<(TEMP_ARR_Y-1);y++){
        for(int x=1;x<(TEMP_ARR_X-1);x++){
            neighbor_avg = (prev_temps[y-1][x] + prev_temps[y][x-1]
                            + prev_temps[y][x+1] + prev_temps[y+1][x])/4;  
            calc_temps[y][x] = neighbor_avg;
            current_change = calc_temps[y][x] - prev_temps[y][x];
            if(current_change > greatest_change){
                greatest_change = current_change;
            }
        }
    }
    return greatest_change;
}

void init_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]){
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

void print_temp_arr(float temps[TEMP_ARR_Y][TEMP_ARR_X]){
    int len_y = TEMP_ARR_Y;
    int len_x = TEMP_ARR_X;
    for(int y=0;y<len_y;y++){
        for(int x=0;x<len_x;x++){
            printf("%6.1f", temps[y][x]);
        }
        printf("\n");
    }
}

void export_csv(float temps[TEMP_ARR_Y][TEMP_ARR_X], const char file_name[]){
    FILE * pFile;
    pFile = fopen(file_name, "w");
    if(pFile != NULL){
        for(int y=0;y<TEMP_ARR_Y;y++){
            for(int x=0;x<TEMP_ARR_X;x++){
                fprintf(pFile, "%.1f,", temps[y][x]);
            }
            fprintf(pFile, "\n");
        } 
    }
}
