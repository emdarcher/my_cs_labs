

#include "Node.h"


Node::Node(int& data, Node*& l, Node*& r){
    this->data = data;
    this->left = l;
    this->right = r;
}
Node::~Node(){}
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
    return height;
}
