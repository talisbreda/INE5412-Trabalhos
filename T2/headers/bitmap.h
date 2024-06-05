#ifndef BITMAP_H
#define BITMAP_H

#include <allocator.h>

class Bitmap : public Allocator
{
public:
    Bitmap() : Allocator() {
        this->bitmap = new char[this->blocks];
        for (int i = 0; i < this->blocks; i++) {
            this->bitmap[i] = 0;
        }
    };
    Bitmap(int size, int blockSize, int algorithm) : Allocator(size, blockSize, algorithm) {};
    int getMemorySize() { return this->size; }
    int getBlockSize() { return this->blockSize; }
    int getAlgorithm() { return this->algorithm; }
    void bitmapManaging();
    void printSummary();

private:
    char *bitmap;
};

#endif