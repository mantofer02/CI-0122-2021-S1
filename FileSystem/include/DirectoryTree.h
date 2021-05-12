#include <vector>

#include "FileDescriptor.h"

class File
{
private:
  FileDescriptor fileDescriptor;
  std::vector<File *> children;

public:
  File(FileDescriptor fileDescriptor);
  ~File();
  File* getChild(std::string name); 
  std::vector<File *> getAllChilds();
  bool appendChild(FileDescriptor fileDescriptor);
  bool addFile(File *file);
  FileDescriptor readFile();
  bool updateFile(File *file);
  bool deleteFile();
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

  void recorrer();
};