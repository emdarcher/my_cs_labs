
#ifndef NODE_H
#define NODE_H

#include "NodeInterface.h"

class Node : public NodeInterface {
    private:

    public:
        Node();
        virtual ~Node();
        virtual int getData();
        virtual NodeInterface * getLeftChild();
        virtual NodeInterface * getRightChild();
        virtual int getHeight();
};

#endif
