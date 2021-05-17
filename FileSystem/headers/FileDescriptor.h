#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <string>
#define NAME_SIZE 256
#define ID_SIZE 4
#define TYPE_SIZE 128 
#define PERMISSION_SIZE 2
#define FILE_SIZE 4
#define USERNAME_SIZE 256
#define TIME_SIZE 8
#define ADDRESS_SIZE 4

//d -rwx user - rwx group - rwx other
// const int permissions_size = 10;

class FileDescriptor
{
public:
  std::string name; 
  int id;
  std::string type;
  bool permissions[10];
  int size;
  std::string username;
  //Time
  int address;

  FileDescriptor();
  FileDescriptor(char * fileDescriptor);
  FileDescriptor(std::string name, int id, bool permissions[10], int size, std::string username);
  char *serialize();
  void SerializeInt32(char (&buf)[4], int val);
  int32_t ParseInt32(const char (&buf)[4]);
};
#endif