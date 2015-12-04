#include "Property.h"

using namespace std;

Property::Property(unsigned int in_id,
        bool in_rental,
        double in_val,
        string in_addr){
    id = in_id;
    //should initialize once
    //id_counter = 0;
    //id = id_counter++;
    rental = in_rental;
    value = in_val;
    address = in_addr;
    taxes = 0.0;
}
Property::~Property(){}

void Property::setAddr(string in_addr){
    address = in_addr;
}

string Property::getAddr(void) const {
    return address;
}

string Property::toString(void) const {
    
    char ret_buff[PROP_OUT_BUFF_SIZE];
    char rental_str[PROP_OUT_BUFF_SIZE];
    rental_str[0] = '\0';
    strcat(rental_str, ((rental)? "Rental":"NOT rental"));
    sprintf(ret_buff, "Property id: %i  Address: %s  %s  Estimated value: %G",
                id, address.c_str(), rental_str,  value);
    string ret_str(ret_buff);
    return ret_str;

}
unsigned int Property::getId(void) const {
    return id;
}
bool Property::getRental(void) const {
    return rental; 
}
double Property::getValue(void) const {
    return value;
}
double Property::getTaxes(void) const {
    return taxes;
}
string Property::taxesString(void) const {
    char ret_buff[PROP_OUT_BUFF_SIZE];
    sprintf(ret_buff, "** Taxes due for property at: %s\n"
                    "\tProperty id:\t\t\t\t%i\n"
                    "\tThis property has an estimated value of:\t%G\n"
                    "\tTaxes due on this property are:\t\t%G",
                    address.c_str(), id, value, taxes);
    string ret_str(ret_buff);
    return ret_str;
}
