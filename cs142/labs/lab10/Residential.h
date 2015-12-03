//header for Residential Class
#ifndef _RESIDENTIAL_H_
#define _RESIDENTIAL_H_
#include "Property.h"
#include <string>

#define VACANT  0
#define OCCUPIED    1

class Residential : public Property {
    private:
        unsigned int vacancy;    
    public:
        Residential(unsigned int in_id,
                bool in_rental,
                double in_val,
                string in_addr,
                unsigned int in_vacancy);
        virtual ~Residential();
        unsigned int getVacancy(void);
        virtual string toString(void);
};

#endif
