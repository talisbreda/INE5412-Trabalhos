#include <allocator.h>
#include <file.h>

Allocator::Allocator() {
    File f;
    f.read_file();
    this->file = f;
    this->size = f.getMemorySize();
    this->blockSize = f.getBlockSize();
    this->algorithm = f.getAlgorithm();
    this->blocks = this->size / this->blockSize;
}

Allocator::Allocator(int size, int blockSize, int algorithm) {
    this->size = size;
    this->blockSize = blockSize;
    this->algorithm = algorithm;
}
