/**
 * @file DirectoryTree
 * @brief This Directory Tree represents a logic
 * structure that will help use implement a File System
 */

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
     * @brief Sets a new FileDescriptor to a File
     * @param fileDescriptor New File Descriptor for it's respective file
     */
    void updateFile(FileDescriptor *fileDescriptor);
    void deleteFile();
  };
  File *root;

public:
  DirectoryTree();
  ~DirectoryTree();

  /**
   * @brief Adds a FileDescriptor to the DirectoryTree
   * @param path Logical path where the FileDescriptor wants to be positioned
   * @param fileDescriptor ptr to a FileDescriptor object
   * @return Status of the positioning of the FileDescriptor in the DirectoryTree
   * SUCCESS or EXIT_ERROR
   */
  bool createFileDescriptor(std::string path, FileDescriptor *fileDescriptor);
  
  /**
   * @brief Method that reads a FileDescriptor inside the DirectoryTree 
   * @param path Logical path where the File resides inside the tree
   * @return A FileDescriptor ptr, if it's the path does not exist inside the
   * DirectoryTree
   */
  FileDescriptor *readFileDescriptor(std::string path);
  
  /**
   * @brief Updates the value of a FileDescriptor whithin the DirectoryTree
   * @param path Logical path where the File resides inside the tree
   * @param fileDescriptor New FileDescriptor for it's respective file
   * @return True is success, false if failure
   */
  bool updateFileDescriptor(std::string path, FileDescriptor *fileDescriptor);
  
  
  /**
   * @brief Removes the value of a FileDescriptor whithin the DirectoryTree
   * @param path Logical path where the File resides inside the tree
   * @return True is success, false if failure
   */
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