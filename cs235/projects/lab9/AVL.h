
#ifndef AVL_H
#define AVL_H


#include "AVLInterface.h"


class AVL : public AVLInterface {
    private:

    public:
        AVL();
        virtual ~AVL();
        virtual NodeInterface * getRootNode();
        virtual bool add(int data);
        virtual bool remove(int data);
};


#endif
