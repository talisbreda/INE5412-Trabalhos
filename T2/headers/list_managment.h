#ifndef LISTMANAGMENT_H
#define LISTMANAGMENT_H

#include <allocator.h>
#include <Node.h>
#include <linkedList.h>
#include <file.h>

class ListManagment : public Allocator {
public:
    ListManagment() : Allocator() {
        // Inicializa a lista de blocos livres
        Node* bloco = new Node(this->size, -1);
        memory_list.insert_back(bloco);
    }


    void execute();
    void allocate_block(int program_size, int program_id, int block_size);
    void deallocate_block(int program_id);
    void print_list();
    void printSummary();

private:
    DoublyLinkedList memory_list;
};

#endif
