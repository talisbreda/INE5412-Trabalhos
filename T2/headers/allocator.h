#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <file.h>
#include <operation_list.h>

class Allocator
{
public:
    Allocator(int size, int blockSize, int algorithm, OperationList operations);

protected:
    int size, blockSize, algorithm;
    int blocks;
    File file;
    OperationList operations;
};

#endif