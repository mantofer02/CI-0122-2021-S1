#include "../include/DirectoryTree.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    DirectoryTree dt;

    FileDescriptor root;
    root.name = "~";

    FileDescriptor gattoSeLaCome;
    root.name = "gattoSeLaCome";

    std::cout << "Arbol:" << std::endl;

    dt.traverse();

    std::cout << "Arbol:" << std::endl;

    dt.createFileDescriptor("~", root);
    dt.createFileDescriptor("~/gattoSeLaCome", gattoSeLaCome);

    dt.traverse();
    return 0;
}
