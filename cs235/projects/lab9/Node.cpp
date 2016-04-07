

#include "Node.h"


Node::Node(int& data, Node* l, Node* r){
    this->data = data;
    this->left = l;
    this->right = r;
}
Node::~Node(){
}
int Node::getData(){
    return data;
}
NodeInterface * Node::getLeftChild(){
    return left;
}
NodeInterface * Node::getRightChild(){
    return right;
}
int Node::getHeight(){
    if((left == NULL) && (right == NULL)){
        return 1;
    } else if(left == NULL){
        return right->getHeight() + 1;
    } else if(right == NULL){
        return left->getHeight() + 1;
    } else {
        int rh = right->getHeight();
        int lh = left->getHeight();
        return ((rh > lh) ? rh : lh) + 1;
    }
}
int Node::getBalance(){
       
    int rh = (this->right != NULL) ? this->right->getHeight() : 0;
    int lh = (this->left != NULL) ? this->left->getHeight() : 0;

    return rh - lh;
}
