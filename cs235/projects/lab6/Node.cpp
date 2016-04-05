

#include "Node.h"

Node::Node(const int& in_data, Node * l, Node * r){
    data = in_data;
    left = l;
    right = r;
}

Node::~Node(){

}


int Node::getData(){
    return data;
}
Node * Node::getLeftChild(){
    return left;
}
Node * Node::getRightChild(){
    return right;
}
