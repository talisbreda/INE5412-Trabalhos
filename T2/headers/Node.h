#ifndef NODE_H
#define NODE_H

struct Node {
    int data_size;
    int ID;
    Node* prev;
    Node* next;

    Node(int data_size, int ID) 
        : data_size(data_size), ID(ID), prev(nullptr), next(nullptr) {}
};

#endif
