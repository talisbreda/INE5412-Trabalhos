#include <list.h>
#include <doublyLinkedList.h>
#include <file.h>

void ListManagment::execute()
{
    
    OperationList operations = this->file.getOperations();
    for (auto i = 0u; i < operations.size(); i++){
        Operation* op = operations[i];
        if (op->getType() == 0){
            int id = op->getId();
            int size = op->getBytesSize();
            int blocksUsed = size / this->blockSize;
        } else if (op->getType() == 1){
            std::cout << "Fui desalocado u_u" << std::endl;
        } else {
            std::cout << "Operação inválida." << std::endl;
        }
    }
}

int ListManagment::allocateBlock(int program_size, int ID) {
    int new_ID = ID;
    if (freeBlocks.getSize() == 0 || program_size > freeBlocks.getSize()) {
        std::cerr << "Não há espaço o suficiente para este programa." << std::endl;
        return -1;  // Indicador de erro
    }

    int total_size = program_size/this->blockSize;
    if (program_size % this->blockSize != 0){
        total_size++;
    }
    
    for(auto i = 0; i < total_size, i++){
        for (j = 0; j < freeBlocks.getSize(); j++){
            if (freeBlocks[j])

        }
    }

    return blockIndex;
}

// Desaloca um bloco dado seu índice
void ListManagment::deallocateBlock(int blockIndex) {
    freeBlocks.allocateBlock(blockIndex);
}

