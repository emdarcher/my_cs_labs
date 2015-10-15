
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define END_CHAR '#'

int main(){
    vector<char> in_chars;
    while(1){
        char tmp_char;
        char end_char;
        scanf("%c%c", &tmp_char, &end_char);
        if(tmp_char == END_CHAR){
            break;
        }
        in_chars.push_back(tmp_char);
    } 
    int size = in_chars.size();
    for(int i=0;i<(size/2);i++){
        if(!(in_chars[i] == in_chars[size - 1 - i])){
            printf("No!\n");
            return 0;
        }
    }
    if(in_chars.size() > 0){
        printf("Yes!\n");
    } else {
        printf("No!\n");
    }
    return 0;
}
