/*
 *  Test Cases:
 *
 *  group sizes:    234, 32, 1241123
 *  tips:           23%, 13%, 7%
 *  CALCULATOR RESULTS:
 *  (note: using calculator PI key value, which is 3.141592654)
 *  number of pizzas (L,M,S):
 *                  (33,1,0,),(4,1,1),(177303,0,2)
 *  Area:           10568.31769,1570.796327,55701606.42
 *  Area/Person:    45.16375081,49.08738522,44.88000498
 *  before tip      495.92, 77.48,  2602822.6
 *  Cost:           609.6816,   87.5524,    2785020.182
 *  rounded:        $610,       $88,        $2785020
 *
 *  PROGRAM RESULTS:
 *  (note: using PI = 3.14159)
 *  number of pizzas (L,M,S):
 *                  (33,1,0),(4,1,1),(177303,0,2)
 *  Area:           10568.308760,1570.795000,55701559.371480
 *  Area/Person:    45.163713,49.087344,44.879967
 *  Cost:           $610,       $88,        $2785020
 *  
 */

//#include <iostream>
#include <stdio.h>
#include <math.h>

//using namespace std;
const double PI = 3.14159;

struct Pizza {
    double price; //in dollars
    double diameter; //in inches
    int people; //amount of people it can serve
};

const struct Pizza largePizza   =   {14.68, 20, 7};
const struct Pizza mediumPizza  =   {11.48, 16, 3};
const struct Pizza smallPizza   =   {7.28,  12, 1};

int num_guests = 0;
int num_large, num_medium, num_small;
double large_area, medium_area, small_area;
double total_area, area_per_guest;
double total_cost;

//function to calculate and return the area, PI*(radius^2)
double get_area(double in_radius){
    return (in_radius*in_radius)*PI;
}

int main(){
    printf("Please enter the number of guests: ");
    scanf("%i", &num_guests);
    //find the number needed of each pizza size
    num_large = num_guests/largePizza.people;
    num_medium = (num_guests % largePizza.people) / mediumPizza.people;
    num_small = ((num_guests % largePizza.people) % mediumPizza.people);
    printf("\t\tNumber of pizzas\n"
            "Large:\t%i\tMedium:\t%i\tSmall:\t%i\n",
            num_large, num_medium, num_small);
    //get individual pizza areas
    large_area = get_area(largePizza.diameter/2);
    medium_area = get_area(mediumPizza.diameter/2);
    small_area = get_area(smallPizza.diameter/2);
    //calculate total area and area per guest
    total_area = (num_large*large_area) 
                + (num_medium*medium_area)
                + (num_small*small_area);
    area_per_guest = total_area/num_guests;
    printf("Total Area:\t%f (in^2)\tArea per guest:\t%f (in^2)\n", 
            total_area, area_per_guest);
    int in_tip_percent;
    printf("Please enter the percent of total price"
            " to be paid as a tip: ");
    scanf("%i", &in_tip_percent);
    //get total cost with no tip
    double total_cost_notip = (num_large*largePizza.price)
                    + (num_medium*mediumPizza.price)
                    + (num_small*smallPizza.price); 
    //calculate total cost with tip
    total_cost = total_cost_notip 
                + (total_cost_notip * (in_tip_percent*0.01));
    printf("Total Cost:\t$%i\n", (int)round(total_cost));
    return 0;
}

