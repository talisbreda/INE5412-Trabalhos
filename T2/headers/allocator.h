#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <file.h>

class Allocator
{
public:
    Allocator();
    Allocator(int size, int blockSize, int algorithm);

protected:
    int size, blockSize, algorithm;
    int blocks;
    File file;
};

#endif