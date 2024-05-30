#ifndef LISTMANAGMENT_H
#define LISTMANAGMENT_H

#include <allocator.h>
#include <Node.h>
#include <LinkedList.h>

class ListManagment : public Allocator {
public:
    ListManagment() : Allocator(), freeBlocks() {}
    ListManagment(int size, int blockSize, int algorithm) : Allocator(size, blockSize, algorithm), freeBlocks() {
        // Inicializa a lista de blocos livres
        int numBlocks = size / blockSize;
        for (int i = 0; i < numBlocks; ++i) {
            freeBlocks.(i);  // Corrigir. A função aqui não deve ser a Allocate
        }
    }

    int getMemorySize() const { return freeBlocks.getSize(); }
    int getBlockSize() const { return freeBlocks.getBlockSize(); }
    int getAlgorithm() const { return freeBlocks.getAlgorithm(); }
    int allocateBlock(int program_size, int ID);
    void deallocateBlock(int blockIndex);
    void printFreeBlocks() const { freeBlocks.print_list(); }

private:
    LinkedList freeBlocks;
};

#endif
