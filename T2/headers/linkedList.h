#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Node.h"

class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(int data_size, int ID);
    void insertBack(int data_size, int ID);
    void remove(int ID);
    void print_list() const;
    int getSize() cont;

private:
    Node* head;
    Node* tail;

    void clear();
};

#endif
