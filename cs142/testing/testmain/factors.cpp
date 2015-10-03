// Code Here
#include <stdio.h>

int main(){
    int inint;
    scanf("%i", &inint);
    //divides by two
    int factorint = inint>>1;
    printf("%i\n", inint); //first factor is number
    do{
        if((inint % factorint) == 0){
            printf("%i\n", factorint);
        }
    } while (--factorint);
    return 0;
}
