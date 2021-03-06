

#ifndef QS_H
#define QS_H

#include "QSInterface.h"
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#define DEBUG 0

class QS : public   QSInterface {

    private:
        unsigned int current_capacity;
        int * elements;
        unsigned int element_cnt;
        void rec_sort(int left, int right);
    public:
        QS();
        ~QS();
        virtual void sortAll();
        virtual int medianOfThree(int left, int right);
        virtual int partition(int left, int right, int pivotIndex);
        virtual string getArray();
        virtual int getSize();
        virtual void addToArray(int value);
        virtual bool createArray(int capacity);
        virtual void clear();

};

#endif
