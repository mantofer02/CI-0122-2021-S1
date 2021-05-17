#include "DirectoryTree.h"
#include "FileSystem.h"



#include <iostream>
#include <cstring>


int main()
{
    // FileSystem fileSystem;
    Storage storage(25 * 1024 * 1024, 0, 64, 2);
    storage.status();
}
