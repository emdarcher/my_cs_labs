
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListInterface.h"

template<typename T>
class LinkedList : public LinkedListInterface<T> {
    private:
        class Node {
            public:
                T data;
                Node* next;
                Node(const T& data_item, Node* next_ptr = NULL); 
        };
        Node* head;
        Node* tail;
        Node* find_node(T value);
    public:
        LinkedList(void);
        virtual ~LinkedList(void);
        virtual void insertHead(T value);
        virtual void insertTail(T value);
        virtual void insertAfter(T value, T insertionNode);
        virtual void remove(T value);
        virtual void clear();
        virtual T at(int index);
        virtual int size();

};


#endif
