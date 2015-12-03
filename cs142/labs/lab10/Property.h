//Header file for the Property class
#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>

using namespace std;

#define PROP_OUT_BUFF_SIZE  1024

class Property {
    private:
        unsigned int id;
        bool rental;
        double value;
        string address;
    public:
        Property(unsigned int in_id,
                bool in_rental,
                double in_val,
                string in_addr);
        virtual ~Property();
        void setAddr(string in_addr);
        string getAddr(void);
        unsigned int getId(void);
        bool getRental(void);
        double getValue(void);         
        virtual string toString(void);
};

#endif
