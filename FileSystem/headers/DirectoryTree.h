#ifndef DIRECTORY_TREE_H
#define DIRECTORY_TREE_H

#include <vector>
#include "FileDescriptor.h"

class DirectoryTree
{
private:
  class File
  {
  private:
    FileDescriptor *fileDescriptor;
    std::vector<File *> children;

  public:
    /**
     * @brief File Constructor 
     * @param fileDescriptor Pointer to a FileDescriptor object 
     */
    File(FileDescriptor *fileDescriptor);
    ~File();
    File *getChild(std::string name);

    /**
     * @brief Method that returns all children child of a File Object 
     * @return Vector with all the children of the directory tree
     */
    std::vector<File *> getAllChilds();

    /**
     * @brief Adds a child a File
     * @param fileDescriptor ptr to a FileDescriptor object
     * @return A copy of the child who wants to be appended
     */
    File *appendChild(FileDescriptor *fileDescriptor);

    /**
     * @brief Method to read a File 
     * @return FileDescriptor ptr from it's respective file
     */
    FileDescriptor *readFile();

    /**
     * @brief Set a new FileDescriptor to a File
     */
    void updateFile(FileDescriptor *fileDescriptor);
    void deleteFile();
  };
  File *root;

public:
  DirectoryTree();
  ~DirectoryTree();
  bool createFileDescriptor(std::string path, FileDescriptor *fileDescriptor);
  FileDescriptor *readFileDescriptor(std::string path);
  bool updateFileDescriptor(std::string path, FileDescriptor *fileDescriptor);
  bool removeFileDescriptor(std::string path);
  
  /**
   * @brief Method to traverse the DirectoryTree from a certain node
   * @details This method uses other methods such as
   * @code
     traverseRecursive(File *node, std::vector<std::string> path)
     traverse(File *node);
     traverse();
   * @endcode
   * @param node File ptr from where to go in the tree
   * @param path Path or route from a file inside the DirectoryTree
   * @return ptr to a File, NULL if an error occurs or if the path 
   * is incorrect
   */
  File *traverseTree(File *node, std::string path);
  File *traverseRecursive(File *node, std::vector<std::string> path);
  void traverse(File *node);
  void traverse();
};

#endif