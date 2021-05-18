#include <iostream>
#include <ostream>
#include <fstream>

#include "DirectoryTree.h"
#include "Storage.h"

#define SUCCESS 1
#define EXIT_ERROR 0

class FileSystem
{
private:
  DirectoryTree directoryTree;
  Storage storage;
  Entry *FAT;

  std::string directory;
  std::string activeFolder;
  std::string user;

public:
  FileSystem();
  ~FileSystem();
  bool checkPermissions(std::string file);
  bool checkPermissions(std::string file, int permissionIndex);
  // validar
  //char* checkPermissions(std::string file);
  //char* checkPermissions(std::string file, int permissionIndex);
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