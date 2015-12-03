
#include "Property.h"
#include "Commercial.h"

using namespace std;

Commercial::Commercial(unsigned int in_id,
        bool in_rental,
        double in_val,
        string in_addr,
        bool in_discounted,
        double in_discount_rate) : Property(in_id, in_rental, in_val, in_addr){
        discounted = in_discounted;
        discount_rate = in_discount_rate;
}
Commercial::~Commercial(){}
bool Commercial::getDiscounted(void){
    return discounted;
}
double Commercial::getDiscountRate(void){
    return discount_rate;
}
string Commercial::toString(void){
    char ret_buff[PROP_OUT_BUFF_SIZE];    
    string prop_str = Property::toString();
    char discounted_str[PROP_OUT_BUFF_SIZE];
    discounted_str[0] = '\0';
    strcat(discounted_str, ((discounted)? "Discounted":"NOT discounted"));
    char discount_str[PROP_OUT_BUFF_SIZE];
    discount_str[0] = '\0';
    if(discounted){
        sprintf(discount_str, "Discount %G", discount_rate);
    }
    sprintf(ret_buff, "%s  %s  %s", prop_str.c_str(), 
            discounted_str, discount_str);
    string out_str(ret_buff);
    return out_str; 
    
}
