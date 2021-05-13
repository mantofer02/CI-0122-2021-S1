#include <iostream>
#include <stdlib.h>
#include "DirectoryTree.h"
#include <ostream>
#include <fstream>

const int storage_size = 50000;

class FileSystem {
  private:
    DirectoryTree directoryTree;
    char storage[storage_size];
    std::string directory;
    std::string activeFolder;
    std::string user;
    int *fat;

  public:
    FileSystem();
    ~FileSystem();
    bool checkPermissions(std::string file);
    // ver nombres, es solicitar mas espacio
    int reallocSpace();
    int write(char *data, std::string file, std::string user);
    bool execute(std::string file, std::string user);

    //REQUIERE: carpeta actual
    char *list();
    bool changeFolder(std::string folder);
    bool upFolder();
    bool create(std::string file, std::string user);
    void read(std::string file, std::string user);
    int append(char *data, std::string file, std::string user);
};