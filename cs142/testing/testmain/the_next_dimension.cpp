#include <iostream>

using namespace std;
//
//Write your functions here
void addValue(int arr[2][2], int val){
    for(int y=0;y<2;y++){
        for(int x=0;x<2;x++){
         arr[y][x]+=val;   
        }
    }
}
void print(int arr[2][2]){
    for(int y=0;y<2;y++){
        for(int x=0;x<2;x++){
         cout << arr[y][x]
            << ((x<1)?" ":"");   
        }
        cout << "\n";
    }
}
//
int main()
{
     int my_array[2][2] = {{5,4},{23,-1}};

     int value;
     cin >> value;

     addValue(my_array, value);

     print(my_array);

     return 0;
}
