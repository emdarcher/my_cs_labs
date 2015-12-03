
#ifndef _COMMERCIAL_H_
#define _COMMERCIAL_H_

#include "Property.h"
#include <string>

#define RENTAL_TAX_RATE 0.012
#define NOT_RENTAL_TAX_RATE 0.01

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
        bool getDiscounted(void) const;
        double getDiscountRate(void) const;
        virtual string toString(void) const;
        //virtual double getTaxes(void) const;
        //virtual string taxesString(void) const;

};

#endif
