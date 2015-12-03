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

using namespace std;

//constants
#define INPUT_BUFF_SIZE     128

#define NO_ERR  0
#define ERRORED 1
#define INTENDED_RETURN 3

#define DOES_NOT_EXIST  -1

int get_word(char * word);
int load_file(vector<Property*> *props, char * filename);
void print_properties(vector<Property*> props);

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

#define TAG_UNKNOWN -1
#define TAG_RESIDENTIAL 0
#define TAG_COMMERCIAL 1

int load_file(vector<Property*> *props, char * filename){

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
    char end_char;
    int line = 0;
    //read in the rest of the file and Car details
    while(fgets(buff, sizeof(buff), props_file_ptr) != NULL){
        //char name[INPUT_BUFF_SIZE];
        //char color[INPUT_BUFF_SIZE];
        //double price = 0;
        char tag[INPUT_BUFF_SIZE];
        int rental_flag = -1;
        int value = -1;
        int discount_flag = -1;
        double discount_rate = 0.0;
        char addr_begin[INPUT_BUFF_SIZE];
        sscanf(buff, "%s", tag);
        int tag_code = TAG_UNKNOWN;

        if(!strcmp(tag, "Commercial")){
            tag_code = TAG_COMMERCIAL;
        } else if(!strcmp(tag, "Residential")){
            tag_code = TAG_RESIDENTIAL;
        }

        int line_error = -1;
        
        if(tag_code == TAG_UNKNOWN){
            printf("Unknown Type in file \"%s\" on line %i: %s\n",
                        filename, line, buff);  
            line_error = ERRORED;
        } else if(tag_code == TAG_COMMERCIAL){
            if(sscanf(buff, "%s %i %i %i %lf %s", tag, &rental_flag, &value, 
                        &discount_flag, &discount_rate, addr_begin) == 6){
                line_error = NO_ERR;
            } else {
                line_error = ERRORED;
            }
        } else if(tag_code == TAG_RESIDENTIAL){
            if(sscanf(buff, "%s %i %i %i %s", tag, &rental_flag, &value, 
                        &discount_flag, addr_begin) == 5){
                line_error = NO_ERR;
            } else {
                line_error = ERRORED;
            }
        }
        
        if(line_error == ERRORED){
            printf("Error reading file \"%s\" line %i: %s\n", 
                    filename, line, buff);
        } else {
            //get address
            //get pointer to the occurence of addr_begin to get full address
            char * addr_ptr = strstr(buff, addr_begin);
            //remove ending newline
            int addr_len = strlen(addr_ptr);
            if(addr_ptr[addr_len - 1] == '\n'){
                addr_ptr[addr_len - 1] = '\0';    
            }
            //make string object
            string addr_string(addr_ptr);
            
            Property* tmp_Property_ptr = new Property(addr_string);
            (*props).push_back(tmp_Property_ptr);
          
        }

        line++;
    }
    printf("Loaded Property information from file \"%s\"\n", filename);
    //close the file
    fclose(props_file_ptr); 
    return NO_ERR;
}

void print_properties(vector<Property*> props){
        
    printf("Properties: \n");
    for(int i=0;i<(props.size());i++){
        string prop_string = (*props[i]).toString();
        printf("%s", prop_string.c_str());
    } 
}
