

#ifndef BST_H
#define BST_H

#include "BSTInterface.h"
#include <iostream>
#include "Node.h"

#define DEBUG 1

class BST : public BSTInterface {

    private:
        Node * root;
        bool rec_add(Node * &in_root, int &in_data);
        bool rec_remove(Node * &in_root, int &in_data);
        void rec_replace_parent(Node * &old_root, Node * &local_root);
    public:
        BST();
        virtual ~BST();
        virtual NodeInterface * getRootNode();
        virtual bool add(int data);
        virtual bool remove(int data);
        virtual void clear();
};


#endif
