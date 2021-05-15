//#include "DirectoryTree.h"
//#include "FileSystem.h"

#include <Storage.h>

#include <iostream>
#include <cstring>


int main()
{
    Storage storage(5000, 0, 512, 2);

    std::ofstream file("diskImage.dd");
    storage.createDiskImage(&file);
    file.close();
}
