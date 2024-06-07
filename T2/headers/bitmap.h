#ifndef BITMAP_H
#define BITMAP_H

#include <allocator.h>

class Bitmap : public Allocator
{
public:
    Bitmap(int size, int blockSize, int algorithm) : Allocator(size, blockSize, algorithm) {
        this->bitmap = new char[this->blocks];
        for (int i = 0; i < this->blocks; i++) {
            this->bitmap[i] = 0;
        }
    };
    ~Bitmap();
    void bitmapManaging(OperationList operations);
    void printSummary(OperationList operations);

private:
    char *bitmap;
};

#endif