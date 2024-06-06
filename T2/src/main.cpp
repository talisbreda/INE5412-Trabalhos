#include <file.h>
#include <operation.h>
#include <bitmap.h>
#include <list_managment.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    File f;
    f.read_file();

    if (f.getType() == 1)
    {
        Bitmap b = Bitmap(f.getMemorySize(), f.getBlockSize(), f.getAlgorithm(), f.getOperations());
        b.bitmapManaging();
        printf("\n");
        b.printSummary();
    }
    else if (f.getType() == 2)
    {
        ListManagment l = ListManagment(f.getMemorySize(), f.getBlockSize(), f.getAlgorithm(), f.getOperations());
        l.execute();
        printf("\n");
        l.printSummary();
    }

    return 0;
}
