
#include "QS.h"

QS::QS(){
    elements = NULL;
    element_cnt = 0;
    current_capacity = 0;
}
QS::~QS(){

    clear();
}
void QS::sortAll(){

}
int QS::medianOfThree(int left, int right){
    //detect errors
    if((elements == NULL)
            || !(left < right) || (left < 0) || (left >= element_cnt) 
            || (right >= element_cnt) || (right < 0)){
        return -1;
    }
    int middle = (left + right)/2;
#if DEBUG
    cout << "input array: " << getArray() << endl;
    cout << "left = " << left << " middle = " << middle 
        << " right = " << right << endl;
#endif
    int * nums[] = { &elements[left], &elements[middle], &elements[right] };
#if DEBUG
    cout << "nums[] = " << "{ " << *nums[0] << "," 
        << *nums[1] << "," << *nums[2] << "}\n"; 
#endif
    bool switches = false;
    if(middle == left){
        if(!(*nums[0] <= *nums[2])){
            int tmp = *nums[0];
            *nums[0] = *nums[2];
            *nums[2] = tmp;
            //middle = right;
        } 
    }else {
        do{
            switches = false; 
            for(int i=0;i<3-1;i++){
                if(!(*nums[i] <= *nums[i+1])){
#if DEBUG
                    cout << *nums[i] << " is not less than " << *nums[i+1] 
                        << " swapping\n";
#endif
                    int tmp = *nums[i];
                    *nums[i] = *nums[i+1];
                    *nums[i+1] = tmp;
                    switches = true;
                }
            }
        } while(switches == true);
    }
    return middle;
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
    if(elements != NULL){
        delete[] elements;
    }
    current_capacity = 0;
    element_cnt = 0;
    //elements = NULL;
}
