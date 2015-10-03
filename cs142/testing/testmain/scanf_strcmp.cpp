// Code Here
#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 16

int main(){
    char inbuff1[BUFF_SIZE];
    char inbuff2[BUFF_SIZE];
    scanf("%s",inbuff1);
    scanf("%s",inbuff2);
    if(!strcmp("yellow",inbuff1) ||
            !strcmp("red",inbuff1)){
        if(!strcmp("circular",inbuff2)){
            printf("apple");
        } else if(!strcmp("oval",inbuff2)){
            printf("mango");
        }
    }
    return 0;
}
