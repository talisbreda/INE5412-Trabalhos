#ifndef LISTMANAGMENT_H
#define LISTMANAGMENT_H

#include <allocator.h>
#include <Node.h>
#include <operation_list.h>
#include <linkedList.h>
#include <file.h>

class ListManagment : public Allocator {
public:
    ListManagment(int size, int blockSize, int algorithm) : Allocator(size, blockSize, algorithm) {
        // Inicializa a lista de blocos livres
        Node* bloco = new Node(this->size, -1);
        memory_list.insert_back(bloco);
    }

    void execute(OperationList operations);
    void first_fit(int program_size, int program_id, int block_size);
    void best_fit(int program_size, int program_id, int block_size);
    void deallocate_block(int program_id);
    void print_list();
    void printSummary(OperationList operations);

private:
    DoublyLinkedList memory_list;
};

#endif
