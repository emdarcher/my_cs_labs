

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
NodeInterface * Node::getLeftChild(){
    return right;
}
NodeInterface * Node::getRightChild(){
    return left;
}
