#include <bitmap.h>
#include <operation_list.h>

void Bitmap::bitmapManaging() {
    OperationList operations = this->operations;
    for (auto i = 0u; i < operations.size(); i++) {
        Operation* op = operations[i];
        if (op->getType() == 0) {
            // Alocação
            int id = op->getId();
            int size = op->getBytesSize();
            int blocksUsed = size / this->blockSize;
            if (size % this->blockSize != 0) {
                blocksUsed++;
            }
            int start = -1;
            int count = 0;
            for (auto j = 0; j < this->size; j++) {
                if (this->bitmap[j] == 0) {
                    if (start == -1) {
                        start = j;
                    }
                    count++;
                } else {
                    start = -1;
                    count = 0;
                }
                if (count == blocksUsed) {
                    break;
                }
            }
            if (count == blocksUsed) {
                op->setStart(start);
                op->setBlocksSize(blocksUsed);
                for (auto j = start; j < start + blocksUsed; j++) {
                    this->bitmap[j] = 1;
                }
            } else {
                std::cout << "Não foi possível alocar o processo " << id << " de tamanho " << size << std::endl;
            }
        } else {
            // Desalocação
            int id = op->getId();
            Operation* allocatedOp = operations.findById(id);
            int start = allocatedOp->getStart();
            int blocksSize = allocatedOp->getBlocksSize();
            for (auto j = start; j < start+blocksSize; j++) {
                this->bitmap[j] = 0;
            }
        }
    }
    for (auto i = 0; i < this->blocks; i++) {
        printf("%d", this->bitmap[i]);
    }
    std::cout << std::endl;
}

void Bitmap::printSummary() {
    int usedBytes = 0;
    int allocatedBytes = 0;
    int deallocatedBytes = 0;

    for (auto i = 0; i < this->blocks; i++) {
        if (this->bitmap[i] == 1) {
            usedBytes += this->blockSize;
        } else if (this->bitmap[i] == 0) {
            deallocatedBytes += this->blockSize;
        }
        allocatedBytes += this->blockSize;
    }

    std::cout << usedBytes << std::endl;
    std::cout << allocatedBytes << std::endl;
    std::cout << deallocatedBytes << std::endl;

    int allocations = 0;
    int deallocations = 0;
    OperationList operations = this->operations;

    for (auto i = 0u; i < operations.size(); i++) {
        if (operations[i]->getType() == 0) {
            allocations++;
        } else if (operations[i]->getType() == 1) {
            deallocations++;
        }
    }

    std::cout << allocations << std::endl;
    std::cout << deallocations << std::endl;
}