#include <vector>

#include "FileDescriptor.h"


class DirectoryTree
{
private:
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
  File *root;

public:
  DirectoryTree();
  ~DirectoryTree();
  bool createFileDescriptor(std::string path, FileDescriptor fileDescriptor);
  FileDescriptor readFileDescriptor(std::string path);
  bool updateFileDescriptor(std::string path, FileDescriptor fileDescriptor);
  bool removeFileDescriptor(std::string path); 
  File* traverseRecursive(File*, std::vector<std::string>);
  void traverse(File *nodo);
  void traverse();
  File* traverseTree(File *node, std::string path);
};