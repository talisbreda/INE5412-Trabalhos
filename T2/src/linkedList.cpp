#include <linkedList.h>
#include <iostream>
#include <Node.h>

// Construtor padrão
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// Destrutor
DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

// Inserção no início da lista
void DoublyLinkedList::insert_front(Node* newNode) {
    if (!newNode) return;

    if (!head) {
        head = tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    } else {
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
    }
}

// Inserção no final da lista
void DoublyLinkedList::insert_back(Node* newNode) {
    if (!newNode) return;

    if (!tail) {
        head = tail = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    } else {
        newNode->prev = tail;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
    }
}

void DoublyLinkedList::insert_after(Node* newNode, Node* currentNode){
    if (!newNode) return;
    if (!currentNode) return;
    if (currentNode == tail){
        tail = newNode;
    }

    newNode->prev = currentNode;
    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

// Remoção de um nó da lista
void DoublyLinkedList::remove(Node* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }

}

void DoublyLinkedList::remove_front() {
    if (!head) return;  // Lista vazia

    head = head->next;

    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;  // Lista ficou vazia
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

int DoublyLinkedList::get_size() const {
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

Node* DoublyLinkedList::get_head() const {
    return head;
}