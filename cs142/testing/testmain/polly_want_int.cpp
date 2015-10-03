// Code Here
#include <stdio.h>
#define IN_ARR_SIZE 64

int main(){
    int inarr[IN_ARR_SIZE];
    int count = 0;
    while(count < IN_ARR_SIZE){
        int tmpint;
        scanf("%i", &tmpint);
        if(tmpint == -1){
            break;
        } else {
            inarr[count] = tmpint;
        }
        count++;
    }
    for(int i=0; i<count; i++){
        printf("%i\n", inarr[i]);
    }
    return 0;
}
