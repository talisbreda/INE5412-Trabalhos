#include <bitmap.h>
#include <file.h>

void Bitmap::bitmapManaging() {
    OperationList operations = this->file.getOperations();
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
                printf("%d %d\n", start, blocksUsed);
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
            printf("%d %d\n", start, blocksSize);
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