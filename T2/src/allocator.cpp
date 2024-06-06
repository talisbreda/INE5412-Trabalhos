#include <allocator.h>
#include <file.h>
#include <operation_list.h>

Allocator::Allocator(int size, int blockSize, int algorithm, OperationList operations) {
    this->size = size;
    this->blockSize = blockSize;
    this->algorithm = algorithm;
    this->blocks = this->size / this->blockSize;
    this->operations = operations;
}
