#include "Property.h"

using namespace std;

Property::Property(unsigned int in_id,
        bool in_rental,
        double in_val,
        string in_addr){
    id = in_id;
    rental = in_rental;
    value = in_val;
    address = in_addr;
}
//Property::Property(string in_addr){
//    address = in_addr;
//}
Property::~Property(){}

void Property::setAddr(string in_addr){
    address = in_addr;
}

string Property::getAddr(void){
    return address;
}

string Property::toString(void){
    
    char ret_buff[PROP_OUT_BUFF_SIZE];
    char rental_str[PROP_OUT_BUFF_SIZE];
    rental_str[0] = '\0';
    strcat(rental_str, ((rental)? "Rental":"NOT rental"));
    sprintf(ret_buff, "Property id: %i  Address: %s  %s  Estimated value: %G",
                id, address.c_str(), rental_str,  value);
    string ret_str(ret_buff);
    return ret_str;

}
unsigned int Property::getId(void){
    return id;
}
bool Property::getRental(void){
    return rental; 
}
double Property::getValue(void){
    return value;
}
