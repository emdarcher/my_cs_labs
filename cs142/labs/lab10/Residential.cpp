//code for Residential Class
#include "Property.h"
#include "Residential.h"

using namespace std;

Residential::Residential(unsigned int in_id,
        bool in_rental,
        double in_val,
        string in_addr,
        unsigned int in_vacancy) : Property(in_id, in_rental, in_val, in_addr){
        vacancy = in_vacancy;
        taxes = value * ((vacancy==OCCUPIED) ? 
                OCCUPIED_TAX_RATE : NOT_OCCUPIED_TAX_RATE);
}

Residential::~Residential(){}

unsigned int Residential::getVacancy(void) const {
    return vacancy;
}

string Residential::toString(void) const {
    char ret_buff[PROP_OUT_BUFF_SIZE];    
    string prop_str = Property::toString();
    char vacancy_str[PROP_OUT_BUFF_SIZE];
    vacancy_str[0] = '\0';
    strcat(vacancy_str, ((vacancy==OCCUPIED)? "occupied":"NOT occupied"));
    sprintf(ret_buff, "%s  %s", prop_str.c_str(), vacancy_str);
    string out_str(ret_buff);
    return out_str; 
}

//double Residential::getTaxes(void) const {
//    return taxes;
//}
