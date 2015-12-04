/*
 *  By Ethan Durrant (2015)
 *
 *  NOTE TO TA's I've been working on this code on a Mac, compiling
 *  using the included Makefile with the code, using the g++ compiler.
 *  I have not had a chance to test it in Visual Studio yet, so not
 *  sure if it works there. The code should compile fine on Linux systems
 *  which have the g++ compiler (the Lab Computer's Linux OS should work).
 *  Just go into the directory where the code is stored via the terminal
 *  then enter `make` to compile the code. To run the code, type `./main.bin` .
 */

//this has to be defined for this to compile in Visual Studio
//not necessary when using g++, but should be kept here anyway
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include "Property.h"
#include "Residential.h"
#include "Commercial.h"

using namespace std;

//constants
#define INPUT_BUFF_SIZE     128

#define NO_ERR  0
#define ERRORED 1
#define INTENDED_RETURN 3

#define TAG_UNKNOWN -1
#define TAG_RESIDENTIAL 0
#define TAG_COMMERCIAL 1

#define SORT_ADDRESS    1
#define SORT_TAXES_DUE  2
#define SORT_NOTHING    3

//function prototypes
int get_word(char * word);
int get_int(int *in_int);
int load_file(vector<Property*> *props, char * filename);
void print_properties(vector<Property*> props);
void remove_EOL_chars(char * str);
void print_tax_report(vector<Property*> props);
int sort_properties(vector<Property*> *props, int sort_type);
int address_str_compare(char * addr0_str, char * addr1_str);

int main(){
    //the main() function of the program
    vector<Property*> properties;
    printf("Where should I read the data from? ");
    char file[INPUT_BUFF_SIZE];
    get_word(file);
    load_file(&properties, file);
    print_properties(properties);
    int option = 0;
    //the sorting selection option, for the Extra Credit
    while(1){
        printf("How do you want your tax report sorted?\n"
               "(1) by Address, (2) by Taxes Due, or (3) Do not sort : "); 
        //check for integer input
        if(get_int(&option) == NO_ERR){
            if((option == SORT_ADDRESS) 
                    || (option == SORT_TAXES_DUE)
                    || (option == SORT_NOTHING) ){
                break; 
            } 
        } 
        printf("INVALID selection, please enter %i, %i, or %i\n",
                SORT_ADDRESS, SORT_TAXES_DUE, SORT_NOTHING);
    }
    sort_properties(&properties, option);
    //print out the tax report after sorting
    print_tax_report(properties);

    return 0;
}

int get_word(char * word){
//get a single word from standard input
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

int get_int(int *in_int){
//gets a single integer from standard input
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

void remove_EOL_chars(char * str){
    //remove ending newline or carriage-return
    while(1){
        int str_len = strlen(str);
        if(str[str_len - 1] == '\n' 
                || str[str_len - 1] == '\r'){
            str[str_len - 1] = '\0';    
        } else {
            break;
        }
    }
}

int load_file(vector<Property*> *props, char * filename){
//load in the Properties from the file with filename

    //FILE pointer for the file operations.
    FILE * props_file_ptr;

    //open the file for reading
    props_file_ptr = fopen(filename, "r");
    //check if the file exists
    if(props_file_ptr == NULL){
        printf("A file with filename \"%s\" doesn't exist!\n", filename);
        fclose(props_file_ptr);
        return ERRORED;
    }
    printf("Opened a file with filename \"%s\"\n", filename);
    char buff[INPUT_BUFF_SIZE];
    //get the value to add to the balance
    //double added_balance;
    //start line count with line 1
    int line = 1;
    //read in the lines from the file
    while(fgets(buff, sizeof(buff), props_file_ptr) != NULL){
        char tag[INPUT_BUFF_SIZE];
        int rental_flag = -1;
        double value = 0.0;
        int discount_flag = -1;
        int vacancy = -1; 
        double vacancy_float_check_var = 0.0;
        double discount_rate = 0.0;
        char addr_begin[INPUT_BUFF_SIZE];
        sscanf(buff, "%s", tag);
        int tag_code = TAG_UNKNOWN;

        if( sscanf(buff, "%s", tag) == 1 ){
            if(!strcmp(tag, "Commercial")){
                tag_code = TAG_COMMERCIAL;
            } else if(!strcmp(tag, "Residential")){
                tag_code = TAG_RESIDENTIAL;
            }
        }
        
        //static value to increment for unique id numbers
        static unsigned int new_id = 0;
       
        //variable to store whether there was an error on a line 
        int line_error = -1;

        if(tag_code == TAG_UNKNOWN){
            printf("Ignoring Unknown Type in file \"%s\" on line %i: %s\n",
                        filename, line, buff);  
            line_error = ERRORED;
        } else if(tag_code == TAG_COMMERCIAL){
            if(sscanf(buff, "%s %i %lf %i %lf %s", tag, &rental_flag, &value, 
                        &discount_flag, &discount_rate, addr_begin) == 6){
                if((discount_rate <= 1)){
                    line_error = NO_ERR;
                    //get address
                    //get pointer to the occurence of 
                    //addr_begin to get full address
                    char * addr_ptr = strstr(buff, addr_begin);
                    //remove ending chars
                    remove_EOL_chars(addr_ptr);
                    //convert to C++ string
                    string addr_str(addr_ptr);
                    Commercial* tmp_Com_ptr = new Commercial(new_id,
                                                                rental_flag,
                                                                value,
                                                                addr_str,
                                                                discount_flag,
                                                                discount_rate); 
                    (*props).push_back(tmp_Com_ptr);
                    new_id++;
                } else {
                    line_error = ERRORED;
                }
            } else {
                line_error = ERRORED;
            }
            if(line_error == ERRORED){
                printf("Ignoring bad COMMERCIAL in input file \"%s\" "
                        "at line %i: %s\n", filename, line, buff);
            }
        } else if(tag_code == TAG_RESIDENTIAL){
            if(sscanf(buff, "%s %i %lf %lf %s", tag, &rental_flag, &value, 
                        &vacancy_float_check_var, addr_begin) == 5){
                //check for integer input for vacancy
                if( (int)vacancy_float_check_var 
                        == (float)vacancy_float_check_var){
                    //if so set the vacancy flag
                    vacancy = (int)vacancy_float_check_var;
                    if((vacancy <= OCCUPIED) && (vacancy >= VACANT)){
                        //get address
                        //get pointer to the occurence of 
                        //addr_begin to get full address
                        char * addr_ptr = strstr(buff, addr_begin);
                        //remove ending newline or carriage-return
                        remove_EOL_chars(addr_ptr);
                        //convert to C++ string
                        string addr_str(addr_ptr);
                        Residential* tmp_Res_ptr = new Residential(new_id,
                                                                    rental_flag,
                                                                    value,
                                                                    addr_str,
                                                                    vacancy); 
                        (*props).push_back(tmp_Res_ptr);
                        new_id++;
                    } else {
                        line_error = ERRORED;
                    }
                } else { 
                    line_error = ERRORED; 
                }
            } else {
                line_error = ERRORED;
            } 
            if(line_error == ERRORED){
                //line_error = ERRORED;
                printf("Ignoring bad RESIDENTIAL in input file \"%s\" "
                        "at line %i: %s\n", filename, line, buff);
            }
        }
        //increment the line count
        line++;
    }
    printf("Loaded Property information from file \"%s\"\n", filename);
    //close the file
    fclose(props_file_ptr); 
    return NO_ERR;
}

void print_properties(vector<Property*> props){
    //print out the strings of the Properties in the vector 
    printf("All valid properties: \n");
    for(int i=0;i<(props.size());i++){
        string prop_string = (*props[i]).toString();
        puts(prop_string.c_str());
    } 
}

void print_tax_report(vector<Property*> props){
    //print out the tax report strings
    printf("NOW PRINTING TAX REPORT:\n");
    for(int i=0;i<(props.size());i++){
        string prop_tax_str = (*props[i]).taxesString();
        puts(prop_tax_str.c_str());
    }
}

int address_str_compare(char * addr0_str, char * addr1_str){
    //returns a value that states if addr1_str is greater
    //than addr0_str by numerical and alphabetical order
    int addr0_num = 0;
    char addr0_end_str[INPUT_BUFF_SIZE];
    //check and see if you can extract an int from the addr
    //if it fails set to -1 for having no number
    if(sscanf(addr0_str, "%i %s", &addr0_num, addr0_end_str) != 2){
        addr0_num = -1; 
    } 
    //do the same with addr1_str
    int addr1_num = 0;
    char addr1_end_str[INPUT_BUFF_SIZE];
    if(sscanf(addr1_str, "%i %s", &addr1_num, addr1_end_str) != 2){
        addr1_num = -1;
    }
    if(addr1_num < addr0_num){
        //if the number is less, than return 1 for greater in 
        //numerical order
        return 1;
    } else if(addr1_num > addr0_num){
        //if greater, return -1 for less-than in numerical order
        return -1;
    } else if(addr1_num == addr0_num){
        //if numbers are equal, or both are -1 from no number
        //then compare the two remaining strings
        //get remaining end strings
        char * addr0_end_str_ptr;
        char * addr1_end_str_ptr;
        //to prevent segfaults from unitialized strings
        if(addr0_num >= 0){
            //if the sscanf was successful, and addr0_end_str initialized
            addr0_end_str_ptr = strstr(addr0_str, addr0_end_str);
        } else {
            //if sscanf failed, there is not a number in the address
            addr0_end_str_ptr = addr0_str;
        }
        //same
        if(addr1_num >= 0){
            addr1_end_str_ptr = strstr(addr1_str, addr1_end_str);
        } else {
            addr1_end_str_ptr = addr1_str;
        }

        //return the result from strcmp() which will the compare
        //the two strings ASCIIbetically (by character order in ASCII)
        return strcmp(addr0_end_str_ptr, addr1_end_str_ptr);
    }
    //return if something else somehow fails 
    //and to stop the compiler's complaints
    return 0;
}

int sort_properties(vector<Property*> *props, int sort_type){
    //sort the properties in the vector in different ways
    int props_size = (*props).size();
    if(sort_type == SORT_TAXES_DUE){
        //sort by taxes due, lowest to greatest
        for(int i=0;i<props_size;i++){
            for(int j=i;j<props_size;j++){
                if((*(*props)[i]).getTaxes() > (*(*props)[j]).getTaxes()){
                    //if lower than tax of current lowest index
                    //swap places
                    Property* tmp_Prop_ptr = (*props)[i];
                    (*props)[i] = (*props)[j];
                    (*props)[j] = tmp_Prop_ptr;
                } 
            }
        } 
        return NO_ERR;
    } else if(sort_type == SORT_ADDRESS){
        //sort by the address, numerically, then alphabetically
        for(int i=0;i<props_size;i++){
            for(int j=i;j<props_size;j++){
                //copy the addresses into C strings
                char i_addr_str[INPUT_BUFF_SIZE];
                i_addr_str[0] = '\0';
                strcat(i_addr_str, (*(*props)[i]).getAddr().c_str());
                char j_addr_str[INPUT_BUFF_SIZE];
                j_addr_str[0] = '\0';
                strcat(j_addr_str, (*(*props)[j]).getAddr().c_str());
                //use address_str_compare function to see if the address
                //at index i is "greater" in order than at index j
                if(address_str_compare(i_addr_str, j_addr_str) > 0){
                    //swap the places if so
                    Property* tmp_Prop_ptr = (*props)[i];
                    (*props)[i] = (*props)[j];
                    (*props)[j] = tmp_Prop_ptr;
                }
            }
        }

        return NO_ERR; 
    } else if(sort_type == SORT_NOTHING){
        return NO_ERR;
    } else {
        return ERRORED;
    }
}
