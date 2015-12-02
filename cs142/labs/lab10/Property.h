//Header file for the Property class
#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>

using namespace std;

class Property {
    private:
        string address;
    public:
        Property(string in_addr);
        virtual ~Property();
        void setAddr(string in_addr);
        string getAddr(void);
        string toString(void);
}

#endif
