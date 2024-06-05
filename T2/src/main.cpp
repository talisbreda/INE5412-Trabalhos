#include <file.h>
#include <array_list.h>
#include <operation.h>
#include <bitmap.h>
#include <list_managment.h>

int main(int argc, char const *argv[])
{

    File f;
    f.read_file();

    if (f.getType() == 1)
    {
        Bitmap b;
        b.bitmapManaging();
        printf("\n");
        b.printSummary();
    }
    else if (f.getType() == 2)
    {
        ListManagment l;
        l.execute();
        printf("\n");
        l.printSummary();
    }

    return 0;
}
