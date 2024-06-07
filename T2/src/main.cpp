#include <file.h>
#include <operation.h>
#include <bitmap.h>
#include <list_managment.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    File f;
    OperationList operations = f.read_file();

    if (f.getType() == 1)
    {
        Bitmap b = Bitmap(f.getMemorySize(), f.getBlockSize(), f.getAlgorithm());
        b.bitmapManaging(operations);
        printf("\n");
        b.printSummary(operations);
    }
    else if (f.getType() == 2)
    {
        ListManagment l = ListManagment(f.getMemorySize(), f.getBlockSize(), f.getAlgorithm());
        l.execute(operations);
        printf("\n");
        l.printSummary(operations);
    }

    for (auto i = 0u; i < operations.size(); i++)
    {
        delete operations[i];
    }
    operations.clear();

    return 0;
}
