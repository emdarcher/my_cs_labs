
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListInterface.h"
#include <stdexcept>

template<typename T>
class LinkedList : public LinkedListInterface<T> {
    private:
        class Node {
            public:
                T data;
                Node* next;
                Node(const T& data_item, Node* next_ptr = NULL){
                    this->data = data_item;
                    this->next = next_ptr;
                }
        };
        Node* head;
        //Node* tail;
        Node* find_node(T value){
            //searches for a node with a matching value, 
            //if found, it returns the Node pointer to it,
            //if not, it returns NULL
            Node* ret_node = head;
            while(ret_node != NULL){
                if(ret_node->data == value){
                    return ret_node;
                }
                ret_node = ret_node->next;
            } 
            return NULL;
        }
        int node_cnt;
    public:
        LinkedList(void){
            this->head = NULL;
            ///this->tail = NULL;
            this->node_cnt = 0;
        }
        virtual ~LinkedList(void){
            clear(); 
        }
        virtual void insertHead(T value){
            Node* srch_node = find_node(value);
            //check for no duplicates
            if(srch_node == NULL){
                head = new Node(value, head);
                node_cnt++;
            }
        
        }
        virtual void insertTail(T value){
            Node* srch_node = find_node(value);
            //check for no duplicates
            if(srch_node == NULL){
                Node* tail = head;
                while(tail->next != NULL){
                    tail = tail->next;
                }  
                Node* new_tail = new Node(value);
                tail->next = new_tail;
                tail = new_tail;
                node_cnt++;
            }
        
        }
        virtual void insertAfter(T value, T insertionNode){
            Node* val_node = find_node(value); 
            Node* ins_node = find_node(insertionNode);
            //check that the insertionNode exists and that
            //no Nodes exist with a value equivalent to the given value
            //(no duplicates)
            if((ins_node != NULL) && (val_node == NULL)){
                Node* new_node = new Node(value, ins_node->next);
                ins_node->next = new_node;
                node_cnt++;
                return;
            }
            return;
        
        }
        virtual void remove(T value){
            if(head != NULL){
                Node* inc_node = head;
                //check if first matches
                if(head->data == value){
                    Node* tmp = head;
                    head = head->next;
                    delete tmp;
                    node_cnt--;
                    return;
                }
                //otherwise loop through next nodes
                while(inc_node->next != NULL){
                    if(inc_node->next->data == value){
                        Node* tmp = inc_node->next;
                        inc_node->next = tmp->next;
                        delete tmp;
                        node_cnt--;
                        return;
                    }
                    inc_node = inc_node->next;
                }
            }
        }
        virtual void clear(){
            if(head != NULL){
                //go through the nodes after head
                while( head->next != NULL ){
                    Node* tmp = head->next;
                    head->next = tmp->next;
                    delete tmp; 
                } 
                //then finally delete head
                delete head;
            }
            node_cnt = 0;
        }
        virtual T at(int index){
            if((index < 0) || (index > node_cnt - 1)){
                //if out of bounds
                throw std::out_of_range("The value of index is out of range!");
            }
            Node* index_node = head;
            for(int i=0; i<index; i++){
                index_node = index_node->next;
            }
            return index_node->data;
        }
        virtual int size(){
            return this->node_cnt; 
        }

};


#endif
