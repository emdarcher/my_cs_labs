
#ifndef NODE_H
#define NODE_H

#include "NodeInterface.h"

class Node : public NodeInterface {
    public:
        Node * left;
        Node * right;
        int data;
        Node(int& data, Node* l = NULL, Node* r = NULL);
        virtual ~Node();
        virtual int getData();
        virtual NodeInterface * getLeftChild();
        virtual NodeInterface * getRightChild();
        virtual int getHeight();
};

#endif
