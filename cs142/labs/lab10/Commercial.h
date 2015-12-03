
#ifndef _COMMERCIAL_H_
#define _COMMERCIAL_H_
#include "Property.h"
#include <string>

class Commercial : public Property {
    private:
        bool discounted;        
        double discount_rate;
    public:
        Commercial(unsigned int in_id,
                bool in_rental,
                double in_val,
                string in_addr,
                bool in_discounted,
                double in_discount_rate);
        virtual ~Commercial();
        bool getDiscounted(void);
        double getDiscountRate(void);
        virtual string toString(void);

};

#endif
