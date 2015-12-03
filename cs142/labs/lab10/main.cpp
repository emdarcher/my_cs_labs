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

int get_word(char * word);
int load_file(vector<Property*> *props, char * filename);
void print_properties(vector<Property*> props);
void remove_EOL_chars(char * str);

int main(){
    vector<Property*> properties;
    printf("Where should I read the data from? ");
    char file[INPUT_BUFF_SIZE];
    get_word(file);
    load_file(&properties, file);
    print_properties(properties);

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
    int line = 0;
    //static unsigned int new_id = 0;
    //read in the lines from the file
    while(fgets(buff, sizeof(buff), props_file_ptr) != NULL){
        char tag[INPUT_BUFF_SIZE];
        int rental_flag = -1;
        double value = 0.0;
        int discount_flag = -1;
        int vacancy = -1; 
        double discount_rate = 0.0;
        char addr_begin[INPUT_BUFF_SIZE];
        sscanf(buff, "%s", tag);
        int tag_code = TAG_UNKNOWN;

        if(!strcmp(tag, "Commercial")){
            tag_code = TAG_COMMERCIAL;
        } else if(!strcmp(tag, "Residential")){
            tag_code = TAG_RESIDENTIAL;
        }

        static unsigned int new_id = 0;
        
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
            if(sscanf(buff, "%s %i %lf %i %s", tag, &rental_flag, &value, 
                        &vacancy, addr_begin) == 5){
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
