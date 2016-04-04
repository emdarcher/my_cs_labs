

#ifndef NODE_H
#define NODE_H

#include "NodeInterface.h"

class Node : public NodeInterface {

    private:
    public:
        int data;
        Node * left;
        Node * right;        
        Node(const int& in_data, Node * l = NULL, Node * r = NULL);
        virtual ~Node();
        virtual int getData();
        virtual NodeInterface * getLeftChild();
        virtual NodeInterface * getRightChild();

};


#endif
