#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <string>

//d -rwx user - rwx group - rwx other
// const int permissions_size = 10;

class FileDescriptor {
  public:
    std::string name;
    int id;
    std::string type;
    std::string location;
    bool permissions[10]; // Cambiemos esta vara por un int? btw donde esta el const??? god, why???
    int size;
    std::string username;
    //Time
};

#endif