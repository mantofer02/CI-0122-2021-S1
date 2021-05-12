#include "DirectoryTree.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    DirectoryTree dt;

    FileDescriptor root;
    root.name = "~";

    std::cout << "Arbol:" << std::endl;

    dt.recorrer();

    std::cout << "Arbol:" << std::endl;

    dt.createFileDescriptor("~", root);

    dt.recorrer();
    return 0;
}
