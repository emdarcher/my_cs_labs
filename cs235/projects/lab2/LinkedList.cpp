

#include "LinkedList.h"

LinkedList::Node::Node(const T& data_item, Node* next_ptr = NULL){
    this->data = data_item;
    this->next = next_ptr;
}
        
Node* LinkedList::find_node(T value){
    Node* ret_node = head;
    while(ret_node != NULL){
        if(ret_node->data == value){
            return ret_node;
        }
    } 
    return NULL;
}
        
LinkedList::LinkedList(void){

    this->head = NULL;
    this->tail = NULL;
}
LinkedList::~LinkedList(void){

}
void LinkedList::insertHead(T value){
    head = new Node(value, head);
}
void LinkedList::insertTail(T value){
    Node* new_tail = new Node(value);
    tail->next = new_tail;
    tail = new_tail;
}
void LinkedList::insertAfter(T value, T insertionNode){
    inc_ptr = head;
    while(inc_ptr != NULL){
        if(inc_ptr->data == insertionNode){
            Node* new_node = new Node(value, inc_ptr->next);
            inc_ptr->next = new_node;
            return;
        }
    }
}
void LinkedList::remove(T value){

}
void LinkedList::clear(){

}
T LinkedList::at(int index){

}
int LinkedList::size(){

}
