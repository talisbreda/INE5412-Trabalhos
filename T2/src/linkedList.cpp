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

void DoublyLinkedList::insert_after(Node* newNode, Node* currentNode) {
    if (!newNode || !currentNode) return;

    newNode->prev = currentNode;
    newNode->next = currentNode->next;

    if (currentNode->next) {
        currentNode->next->prev = newNode; // Update the prev pointer of the node after the new node
    } else {
        tail = newNode; // Update tail if currentNode is the current tail
    }

    currentNode->next = newNode; // Update the next pointer of the current node
}


// Remoção de um nó da lista
void DoublyLinkedList::remove(Node* node) {
    node->data_size = 0;
    node->free = true;
}


void DoublyLinkedList::remove_front() {
    if (!head) return;  // Lista vazia

    head = head->next;

    if (head) {
        head->prev = nullptr;
        delete head->prev;
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