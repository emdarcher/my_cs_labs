
#include "QS.h"

QS::QS(){
    element_cnt = 0;
}
QS::~QS(){}
void QS::sortAll(){

}
int QS::medianOfThree(int left, int right){

    return -1;
}
int QS::partition(int left, int right, int pivotIndex){
    return -1;
}
string QS::getArray(){
    //string out_str = "";
    stringstream out_ss;
    for(int i=0;i<element_cnt;i++){
        //out_str += itoa(elements[i]);
        out_ss << elements[i];
        if(i != element_cnt - 1){
            //out_str += ",";
            out_ss << ",";
        }
    }
    //return out_str;
    return out_ss.str();
}
int QS::getSize(){
    return element_cnt; 
}
void QS::addToArray(int value){
    if(element_cnt == current_capacity){
        return;
    }
    elements[element_cnt] = value;
    element_cnt++;
}
bool QS::createArray(int capacity){
//dynamically allocate array with size of capacity
    
    if(capacity < 0){
        return false;
    }
    if(elements != NULL){
        delete[] elements;
    }
    current_capacity = capacity;
    elements = new int[capacity];
    return true;
}
void QS::clear(){
    delete[] elements;
    current_capacity = 0;
    element_cnt = 0;
    //elements = NULL;
}
