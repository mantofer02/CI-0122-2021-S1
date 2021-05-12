#include "DirectoryTree.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    DirectoryTree dt;

    FileDescriptor pana;
    pana.name = "El pana";

    std::cout << pana.name << std::endl;
    return 0;
}
