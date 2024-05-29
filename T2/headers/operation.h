#ifndef OPERATION_H
#define OPERATION_H

class Operation 
{
    public:
        Operation();
        Operation(int type, int id, int size);
        int getType();
        int getId();
        int getBytesSize();
        int getStart();
        void setStart(int start);
        int getBlocksSize();
        void setBlocksSize(int blocksSize);

    private:
        int type, id, bytesSize, blocksSize;
        int start = -1;
};

#endif