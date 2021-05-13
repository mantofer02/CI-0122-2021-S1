#include "DirectoryTree.h"
#include <iostream>

int main()
{
    DirectoryTree dt;

    FileDescriptor root;
    root.name = "~";

    FileDescriptor A;
    A.name = "A";

    FileDescriptor B;
    B.name = "B";

    FileDescriptor C;
    C.name = "C";


    FileDescriptor D;
    D.name = "D";
    
    std::cout << "Arbol: " << std::endl;
    dt.traverse();

    dt.createFileDescriptor("", &root);
    dt.createFileDescriptor("~", &A);
    dt.createFileDescriptor("~/A", &B);
    dt.createFileDescriptor("~/A", &C);
    dt.createFileDescriptor("~", &D);
    dt.createFileDescriptor("~", &B);

    std::cout << "Arbol: " << std::endl;
    dt.traverse();

    FileDescriptor fd;
    fd.name = "newName";
    dt.updateFileDescriptor("~/A", &fd);

    std::cout << "Arbol: " << std::endl;\
    dt.traverse();
    return 0;
}
