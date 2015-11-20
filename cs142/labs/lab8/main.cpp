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
#define INTENDED_RETURN 3

#define DOES_NOT_EXIST  -1

//function prototypes
int run_menu(void);
int get_int(int *in_int);
int get_double(double *in_double);
int get_word(char * word);
void show_inv(vector<Car*> inv);
void show_bal(double bal);
int buy_car(vector<Car*> *inv, double * bal);
int sell_car(vector<Car*> *inv, double * bal);
int paint_car(vector<Car*> *inv);
int load_file(vector<Car*> *inv, double * bal);
int save_file(vector<Car*> inv, double bal);

int car_exists(vector<Car*> inv, char * name);
void remove_car(vector<Car*> *inv, int index);

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
                error = sell_car(&inventory, &balance);
                break;
            case PAINT_A_CAR:
                error = paint_car(&inventory);
                break;
            case LOAD_FILE:
                error = load_file(&inventory, &balance);
                break;
            case SAVE_FILE:
                error = save_file(inventory, balance);
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

int car_exists(vector<Car*> inv, char * name){
    //returns index in vector where a Car with the name exists 
    for(int i=0;i<inv.size();i++){
        string car_name = (*inv[i]).getName();
        if(!strcmp(name, car_name.c_str())){
            return i;
        }
    }
    return DOES_NOT_EXIST;
}

void remove_car(vector<Car*> *inv, int index){
    Car * tmp_Car_ptr = (*inv)[index];
    //deallocate the pointer
    delete tmp_Car_ptr;
    //erase the pointer from the vector
    (*inv).erase((*inv).begin() + index); 
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
    if(car_exists(*inv, name) != DOES_NOT_EXIST){
        printf("Car with name \"%s\" already exists!\n", name);
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

int sell_car(vector<Car*> *inv, double * bal){
    char name[INPUT_BUFF_SIZE];
    printf("Enter name of the Car: ");
    get_word(name);
    int car_index = car_exists(*inv, name);
    if(car_index == DOES_NOT_EXIST){
        printf("A Car with name \"%s\" does not exist in the inventory.\n",
                name);
        return ERRORED;
    }
    Car* tmp_Car_ptr = (*inv)[car_index];
    //get the price of the Car before we "sell" it
    double sell_price = (*tmp_Car_ptr).getPrice();
    //"sell" the car, add the price back into the balance
    *bal += sell_price;
    //remove the Car from the vector
    remove_car(inv, car_index);
    printf("Removed Car with name \"%s\" from the inventory.\n"
            "Sold for $%0.2lf\n", name, sell_price);
    return NO_ERR;
}

int paint_car(vector<Car*> *inv){
    char name[INPUT_BUFF_SIZE];
    char color[INPUT_BUFF_SIZE];
    printf("Enter name of the Car to paint: ");
    get_word(name);
    int car_index = car_exists(*inv, name);
    if(car_index == DOES_NOT_EXIST){
        printf("A Car with name \"%s\" does not exist in the inventory.\n",
                name);
        return ERRORED;
    }
    printf("Enter the color to paint the Car: ");
    get_word(color); 
    string color_string(color);
    (*(*inv)[car_index]).paint(color_string);
    printf("Painted Car with name \"%s\" the color %s\n", name, color);
    return NO_ERR;
}

int load_file(vector<Car*> *inv, double * bal){
    char filename[INPUT_BUFF_SIZE];

    //FILE pointer for the file operations.
    FILE * inv_file_ptr;
    printf("Enter filename of the inventory file to load: ");
    get_word(filename);

    //open the file for reading
    inv_file_ptr = fopen(filename, "r");
    //check if the file exists
    if(inv_file_ptr == NULL){
        printf("A file with filename \"%s\" doesn't exist!\n", filename);
        fclose(inv_file_ptr);
        return ERRORED;
    }
    printf("Opened a file with filename \"%s\"\n", filename);
    char buff[INPUT_BUFF_SIZE];
    //get the value to add to the balance
    double added_balance;
    char end_char;
    fgets(buff, sizeof(buff), inv_file_ptr);
    if(sscanf(buff, "%lf%c", &added_balance, &end_char) != 2){
        printf("Error reading balance from first line of file.\n");
        fclose(inv_file_ptr);
        return ERRORED;
    } else {
        //add the balance from the file to our current balance
        *bal += added_balance;
    }
    int line = 1;
    //read in the rest of the file and Car details
    while(fgets(buff, sizeof(buff), inv_file_ptr) != NULL){
        char name[INPUT_BUFF_SIZE];
        char color[INPUT_BUFF_SIZE];
        double price = 0;
        if(sscanf(buff, "%s %s %lf", name, color, &price) == 3){
            string name_string(name);
            string color_string(color);
            Car* tmp_Car_ptr = new Car(name_string, color_string, price);
            (*inv).push_back(tmp_Car_ptr);
        } else {
            printf("Error reading line %i from file \"%s\"\n", line, filename);
            fclose(inv_file_ptr);
            return ERRORED;
        }
        line++;
    }
    printf("Loaded Inventory information from file \"%s\"\n", filename);
    //close the file
    fclose(inv_file_ptr); 
    return NO_ERR;
}

int save_file(vector<Car*> inv, double bal){
    char filename[INPUT_BUFF_SIZE];

    //FILE pointer for the file operations.
    FILE * inv_file_ptr;
    printf("Enter filename of the file to save the inventory in: ");
    get_word(filename);
 
    //check if file already exists, ask if they want to continue
    if(fopen(filename, "r") != NULL){
        while(1){
            printf("A file with name \"%s\" already exists!\n"
                    "Do you want to continue and overwrite the file?\n"
                    "( enter 1 to continue, or 2 to go back to the menu): ",
                    filename);
            int choice = 0;
            if(get_int(&choice) == NO_ERR){
                if(choice == 1){
                    break;
                } else if(choice == 2){
                    printf("Returning to menu...\n");
                    return INTENDED_RETURN;
                } else {
                    printf("Must enter 1 or 2!\n");
                }
            }
        }
    }

    //open file for writing
    inv_file_ptr = fopen(filename, "w");
    printf("Opened file with name: %s\n", filename);
    //enter in the balance value
    fprintf(inv_file_ptr, "%0.2lf\n", bal);
    //enter in the Cars from the vector on each following line
    for(int i=0;i<inv.size();i++){
        string name_string = (*inv[i]).getName();
        string color_string = (*inv[i]).getColor();
        double price = (*inv[i]).getPrice(); 
        fprintf(inv_file_ptr, "%s %s %0.2lf\n", 
                name_string.c_str(), color_string.c_str(), price);
    } 
    printf("Saved Inventory to file with name: %s\n", filename);
    //close the file
    fclose(inv_file_ptr);
    return NO_ERR;
}

int get_word(char * word){
    char buf[INPUT_BUFF_SIZE];
    char tmp_word[INPUT_BUFF_SIZE];
    //get a line from standard input 
    fgets( buf, sizeof(buf), stdin);
    //check for string input
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
