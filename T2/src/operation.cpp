#include <operation.h>

Operation::Operation() {
    this->type = -1;
    this->id = -1;
    this->bytesSize = -1;
    this->blocksSize = -1;
}

Operation::Operation(int type, int id, int size) {
    this->type = type;
    this->id = id;
    this->bytesSize = size;
    this->blocksSize = -1;
}

int Operation::getType() {
    return this->type;
}

int Operation::getId() {
    return this->id;
}

int Operation::getBytesSize() {
    return this->bytesSize;
}

void Operation::setStart(int start) {
    this->start = start;
}

int Operation::getStart() {
    return this->start;
}

int Operation::getBlocksSize() {
    return this->blocksSize;
}

void Operation::setBlocksSize(int blocksSize) {
    this->blocksSize = blocksSize;
}