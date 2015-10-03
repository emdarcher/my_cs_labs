/*
 * TEST CASES:
 *  test1: {
 *  mpy: 58076
 *  gal_price: 4.89
 *  h_init_cost: 18000
 *  h_mpg: 32
 *  h_resale: 15000
 *  nh_init_cost: 16000
 *  nh_mpg: 23
 *  nh_resale: 12000
 *  criterion: Total
 *  calc_result:
 *  hybrid: total_gal=9074.375 total_cost=47373.69375
 *  non-hybrid: total_gal=12625.21739 total_cost=65737.31304
 *  comp_result:
 *  Car Type:   hybrid
 *  total gallons:  9074.375000
 *  total cost: 47373.693750
 *  Car Type:   non-hybrid
 *  total gallons:  12625.217391
 *  total cost: 65737.313043
 *  } 
 *  test2: {
 *  mpy: 15832
 *  gal_price: 3.92
 *  h_init_cost: 21000
 *  h_mpg: 46
 *  h_resale: 18000
 *  nh_init_cost: 18000
 *  nh_mpg: 28
 *  nh_resale: 14000
 *  criterion: Total
 *  calc_result:
 *  hybrid:     total_gal=1720.869565  total_cost=9745.808696
 *  non-hybrid: total_gal=2827.142857  total_cost=15082.4
 *  comp_result:
 *  Car Type:   hybrid
 *  total gallons:  1720.869565
 *  total cost: 9745.808696
 *  Car Type:   non-hybrid
 *  total gallons:  2827.142857
 *  total cost: 15082.400000
 *  } 
 *  test3: {
 *  mpy: 4782
 *  gal_price: 4.79
 *  h_init_cost: 1745
 *  h_mpg: 61
 *  h_resale: 1456
 *  nh_init_cost: 14000
 *  nh_mpg: 18
 *  nh_resale: 10000
 *  criterion: Total
 *  calc_result:
 *  hybrid:     total_gal=391.9672131  total_cost=2166.522951
 *  non-hybrid: total_gal=1328.333333  total_cost=10362.71667
 *  comp_result:
 *  Car Type:   hybrid
 *  total gallons:  391.967213
 *  total cost: 2166.522951
 *  Car Type:   non-hybrid
 *  total gallons:  1328.333333
 *  total cost: 10362.716667
 *  } 
 *
 *  EXTRA CREDIT RESULTS:
 *  Assume that
 *
 *      A new, non-hybrid car costs $15,000 and gets 25 mpg
 *      A new hybrid car costs $32,000
*       You resell any car after 5 years for 75% its original value
*       You drive 10,000 miles in a year
*       Gas costs $2.50
*
 *  The gas milage needed for the hybrid over 5 years to have a total cost
 *  equal to the non-hybrid car.
 *  The answer: 166.666668 mpg
 * 
 *  The extra credit calculation program can be run be calling the program
 *  with the the argument `--extra-credit` in the command line.
 */

//#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

//using namespace std;

#define YEARS           5
#define EC_THRESHOLD    0.000001
#define EC_STEP_AMOUNT  0.000001

struct Car {
    char name_str[16];
    double init_cost;
    double eff_mpg;
    double est_resale_value;
}; 

struct Car hybridCar        = {"hybrid",0,0,0};
struct Car non_hybridCar    = {"non-hybrid",0,0,0};

// function that makes a prompt for a double value, and reprompts
// if the input number is less than or equal to zero
void reprompt_double(const char * prompt, const char * format, 
                            double &var){
    int loop_var = 1;
    double tmp_double;
    while(loop_var){
        printf(prompt);
        scanf(format, &tmp_double);
        if(!(tmp_double <= 0)){
            var = tmp_double;
            break;
        } else {
            printf("input number must be greater than 0!\n");
        }
    }
}

double total_gallons(double mpy, double mpg, int years); 
double total_cost(double tot_gal, double gal_price, double init_cost,
                    double resale_value);
void print_car_results(struct Car inCar, double tot_gal,double tot_cost);


double hybrid_total_gal; 
double hybrid_total_cost;
double non_hybrid_total_gal;
double non_hybrid_total_cost;
double est_mpy, est_gal_price;

int main(int argc, char ** args){
    //double init_hybrid_cost, hybrid_mpg, hybrid_resale;
    //double init_reg_cost, reg_mpg, reg_resale;
    char user_criterion[8];
    char tmp_str[128];
    if(argc > 1){
        printf("has %i args\n", argc);
    if(!strcmp("--extra-credit", args[1])){
        printf("running extra credit calculation\n");
        non_hybridCar.init_cost = 15000;
        non_hybridCar.eff_mpg = 25;
        hybridCar.init_cost = 32000;
        non_hybridCar.est_resale_value = non_hybridCar.init_cost * 0.75;
        hybridCar.est_resale_value = hybridCar.init_cost * 0.75;
        est_mpy = 10000;
        est_gal_price = 2.50;
        non_hybrid_total_gal = total_gallons(est_mpy,non_hybridCar.eff_mpg,
                                    YEARS);
        non_hybrid_total_cost = total_cost(non_hybrid_total_gal, 
                                        est_gal_price, 
                                        non_hybridCar.init_cost,
                                        non_hybridCar.est_resale_value);
        hybridCar.eff_mpg = 1;
        do{
            hybrid_total_gal = total_gallons(est_mpy, hybridCar.eff_mpg,YEARS);
            hybrid_total_cost = total_cost(hybrid_total_gal, est_gal_price, 
                                        hybridCar.init_cost, 
                                        hybridCar.est_resale_value);
            hybridCar.eff_mpg += EC_STEP_AMOUNT; 
        } while(!(fabs(hybrid_total_cost - non_hybrid_total_cost) 
                    < EC_THRESHOLD)); 
        printf("needed mpg for hybrid is: %f\n", hybridCar.eff_mpg);
        return 0;
    }
    }
    printf("Enter the following values: \n");
    reprompt_double("The estimated miles driven per year: ", "%lf", est_mpy);
//    printf("entered: %f", est_mpy);
    sprintf(tmp_str, "The estimated price of a gallon of gas during the "
                    "%i years of ownership: ", YEARS);
    reprompt_double(tmp_str, "%lf", est_gal_price);
    reprompt_double("The initial cost of a hybrid car: ", 
                    "%lf", hybridCar.init_cost);
    reprompt_double("The efficiency of the hybrid car in miles per gallon: ",
                    "%lf", hybridCar.eff_mpg);
    sprintf(tmp_str, "The estimated resale value (a dollar amount) for a "
                    "hybrid after %i years: ", YEARS);
    reprompt_double(tmp_str, "%lf", hybridCar.est_resale_value);
    reprompt_double("The initial cost of a non-hybrid car: ", 
                    "%lf", non_hybridCar.init_cost);
    reprompt_double("The efficiency of the non-hybrid car in "
                    "miles per gallon: ", "%lf", non_hybridCar.eff_mpg);
    sprintf(tmp_str,"The estimated resale value (a dollar amount) for "
                    "a non-hybrid after %i years: ", YEARS);
    reprompt_double(tmp_str, "%lf",non_hybridCar.est_resale_value);
    printf("Enter criterion (\"Gas\" or \"Total\"): ");
    scanf("%s", user_criterion);

    hybrid_total_gal = total_gallons(est_mpy, hybridCar.eff_mpg,YEARS);
    hybrid_total_cost = total_cost(hybrid_total_gal, est_gal_price, 
                                hybridCar.init_cost, hybridCar.est_resale_value);
    non_hybrid_total_gal = total_gallons(est_mpy, non_hybridCar.eff_mpg,YEARS);
    non_hybrid_total_cost = total_cost(non_hybrid_total_gal, 
                                    est_gal_price, non_hybridCar.init_cost,
                                    non_hybridCar.est_resale_value);
    if(!strcmp("Gas", user_criterion)){
        if(hybrid_total_gal <= non_hybrid_total_gal){
            print_car_results(hybridCar, hybrid_total_gal, hybrid_total_cost);
            print_car_results(non_hybridCar, non_hybrid_total_gal, 
                                non_hybrid_total_cost);
        } else {
            print_car_results(non_hybridCar, non_hybrid_total_gal, 
                                non_hybrid_total_cost);
            print_car_results(hybridCar, hybrid_total_gal, hybrid_total_cost);
        }
    } else if(!strcmp("Total", user_criterion)){
        if(hybrid_total_cost <= non_hybrid_total_cost){
            print_car_results(hybridCar, hybrid_total_gal, hybrid_total_cost);
            print_car_results(non_hybridCar, non_hybrid_total_gal, 
                                non_hybrid_total_cost);
        } else {
            print_car_results(non_hybridCar, non_hybrid_total_gal, 
                                non_hybrid_total_cost);
            print_car_results(hybridCar, hybrid_total_gal, hybrid_total_cost);
        }
    }
    return 0;
}

void print_car_results(struct Car inCar, double tot_gal,double tot_cost){
    printf("Car Type:\t%s\ntotal gallons:\t%f\ntotal cost:\t%f\n",
            inCar.name_str, tot_gal, tot_cost);
}

double total_gallons(double mpy, double mpg, int years){
    return (double)((mpy/mpg)*years);
}

double total_cost(double tot_gal, double gal_price, double init_cost,
                    double resale_value){
    double cost = 0;
    //double tot_gal = total_gallons(mpy, mpg, years);
    cost = (tot_gal*gal_price) + (init_cost - resale_value);
    return cost;
} 

