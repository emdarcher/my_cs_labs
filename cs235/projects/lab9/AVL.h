
#ifndef AVL_H
#define AVL_H


#include "AVLInterface.h"
#include "Node.h"
#include <math.h>

class AVL : public AVLInterface {
    private:
        Node * root;
        void rot_right(Node*& local_root);
        void rot_left(Node*& local_root);
        bool rec_add(Node * &in_root, int &in_data);
        bool rec_remove(Node * &in_root, int &in_data);
        void rec_replace_parent(Node * &old_root, Node * &local_root);
        void rec_balance(Node*& in_root);
        void clear();
    public:
        AVL();
        virtual ~AVL();
        virtual NodeInterface * getRootNode();
        virtual bool add(int data);
        virtual bool remove(int data);
};


#endif
