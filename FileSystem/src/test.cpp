//#include "DirectoryTree.h"
//#include "FileSystem.h"

#include <Storage.h>

#include <iostream>
#include <cstring>


int main()
{
    Storage storage(25 * 1024 * 1024, 0, 64, 2);

    std::ofstream file("diskImage.dd");
    storage.createDiskImage(&file);
    file.close();

    storage.status();

}
