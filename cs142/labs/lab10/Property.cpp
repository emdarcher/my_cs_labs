#include "Property.h"

using namespace std;

Property::Property(string in_addr){
    address = in_addr;
}
Property::~Property(){}

void Property::setAddr(in_addr){
    address = in_addr;
}

string Property::getAddr(void){
    return address;
}

string Property::toString(void){
    stringstream ss;
    ss << "Address: " << address << "\n";
    return ss.str();
}
