#include <list>

#include "FileDescriptor.h"

class File
{
private:
  FileDescriptor fileDescriptor;
  std::list<File *> children;

public:
  File(FileDescriptor fileDescriptor);
  ~File();
  bool addChildren(File *file);
  bool removeChildren(File *file);
};

class DirectoryTree
{
private:
  File *root;

public:
  DirectoryTree();
  ~DirectoryTree();
  bool createFileDescriptor(std::string path, FileDescriptor fileDescriptor);
  FileDescriptor readFileDescriptor(std::string path);
  bool updateFileDescriptor(std::string path, FileDescriptor fileDescriptor);
  bool removeFileDescriptor(std::string path); 
};