#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Node.h"

class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insert_front(Node* node);
    void insert_back(Node* node);
    void remove(Node* node);
    void remove_front();
    void print_list() const;
    int get_size() const;
    Node* get_head() const;
    void insert_after(Node* newNode, Node* currentNode);

private:
    Node* head;
    Node* tail;

    void clear();
};

#endif
