/**
 * @file FileDesciptor structure that helps 
 * mantain the Descriptions of a File Object
 */


#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <string>
#include <vector>
#include <ctime>
#define NAME_SIZE 256
#define ID_SIZE 4
#define TYPE_SIZE 128 
#define PERMISSION_SIZE 2
#define FILE_SIZE 4
#define USERNAME_SIZE 256
#define TIME_SIZE 8
#define ADDRESS_SIZE 4

// ver si es necesario el dissable para 
// cada permiso
#define R_PERMISSION 4
#define W_PERMISSION 2
#define X_PERMISSION 1

#define DISSABLE_ALL 0
#define ENABLE_RWX 7

#define SUCCESS 1
#define EXIT_ERROR 0

//d -rwx user - rwx group - rwx other
// const int permissions_size = 10;

class FileDescriptor
{
public:
  std::string name; 
  int id;
  std::string type;
  //bool permissions[10];
  char permissions[2];
  int size;
  std::string username;
  time_t time = std::time(0);
  int address;

  FileDescriptor();
  FileDescriptor(char * fileDescriptor);
  FileDescriptor(std::string name, int id, char permissions[2], int size, std::string username);
  std::vector<char> serialize();
  void pushString(std::string element, int counter, std::vector<char> *buffer);
  void pushInteger(int element, std::vector<char> *buffer);
  void pushTime(time_t element, std::vector<char> *buffer);
  void pushPermission(char (&element)[2], std::vector<char> *buffer);
  void SerializeInt32(char (&buf)[4], int val);
  void SerializeInt64(char (&buf)[8], long val);
  bool updateUserPermission(int newPermission);
  bool updateGroupPermission(int newPermission);
  bool updateAllPermission(int newPermission);
  int32_t ParseInt32(const char (&buf)[4]);
};
#endif