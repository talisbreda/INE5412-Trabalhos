#include "DoublyLinkedList.h"
#include <iostream>

// Construtor padrão
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Destrutor
DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

// Inserção no início da lista
void DoublyLinkedList::insertFront(int data_size, int ID) {
    Node* newNode = new Node(data_size, ID);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

// Inserção no final da lista
void DoublyLinkedList::insertBack(int data_size, int ID) {
    Node* newNode = new Node(data_size, ID);
    if (!tail) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

// Remoção de um nó da lista
void DoublyLinkedList::remove(int ID) {
    Node* current = head;
    while (current) {
        if (current->ID == ID) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            delete current;
            return;
        }
        current = current->next;
    }
}

// Impressão da lista do início ao fim
void DoublyLinkedList::print_list() const {
    Node* current = head;
    while (current) {
        std::cout << "ID: " << current->ID << ", Data Size: " << current->data_size << std::endl;
        current = current->next;
    }
}

int DoublyLinkedList::getSize() const {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}



// Limpeza da lista
void DoublyLinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}
