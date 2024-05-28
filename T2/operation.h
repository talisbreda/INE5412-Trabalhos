#ifndef OPERATION_H
#define OPERATION_H

class Operation 
{
    public:
        Operation(int type, int id, int size);
        int getType();
        int getId();
        int getSize();

    private:
        int type, id, size;
};

#endif