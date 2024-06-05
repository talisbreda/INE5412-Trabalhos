#ifndef BITMAP_H
#define BITMAP_H

#include <allocator.h>

class Bitmap : public Allocator
{
public:
    Bitmap(int size, int blockSize, int algorithm, OperationList operations) : Allocator(size, blockSize, algorithm, operations) {
        this->bitmap = new char[this->blocks];
        for (int i = 0; i < this->blocks; i++) {
            this->bitmap[i] = 0;
        }
    };
    void bitmapManaging();
    void printSummary();

private:
    char *bitmap;
};

#endif