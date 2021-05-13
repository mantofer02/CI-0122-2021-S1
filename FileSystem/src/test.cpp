#include "../include/DirectoryTree.h"
#include <iostream>

int main(int argc, char const *argv[])
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
    

    dt.traverse();

    dt.createFileDescriptor("", root);
    dt.createFileDescriptor("~", A);
    dt.createFileDescriptor("~/A", B);
    dt.createFileDescriptor("~/A", C);
    dt.createFileDescriptor("~", D);


    dt.traverse();
    return 0;
}
