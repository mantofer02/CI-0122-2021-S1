#include "FileDescriptor.h"

FileDescriptor::FileDescriptor()
{
    this->name = "";
    this->id = 0;
    this->type = "";
    this->size = 0;
    this->username = "";
    this->address = -1;
    for (int i = 0; i < 2; ++i)
    {
      // Validar Mapeo
      this->permissions[i] = '0';
    }
}

FileDescriptor::FileDescriptor(char *fileDescriptor)
{
}

FileDescriptor::FileDescriptor(std::string name, int id, char permissions[2], int size, std::string username)
{
    this->name = name;
    this->id = id;
    for (int i = 0; i < 2; ++i)
    {
        this->permissions[i] = permissions[i];
    }
    this->size = size;
    this->username = username;
}

std::vector<char> FileDescriptor::serialize()
{
  // se quito el counter de Int, Time y Permissions
    std::vector<char> buffer;
    pushString(this->name, NAME_SIZE, &buffer);
    pushInteger(this->id, &buffer);
    pushString(this->type, TYPE_SIZE, &buffer);
    pushPermission(this->permissions, &buffer);
    pushInteger(this->size, &buffer);
    pushString(this->username, USERNAME_SIZE, &buffer);
    pushTime(this->time, &buffer);
    pushInteger(this->address, &buffer);
    return buffer;
}

void FileDescriptor::pushInteger(int element, std::vector<char> *buffer)
{
  char intBuffer[4];
  SerializeInt32(intBuffer, element);
  for (int i = 0; i < 4; ++i)
  {
    buffer->push_back(intBuffer[i]);
  }
}

void FileDescriptor::pushString(std::string element, int counter, std::vector<char> *buffer)
{
  for (auto character : element)
  {
    buffer->push_back(character);
    --counter;
  }
  while (counter > 0)
  {
    buffer->push_back(' ');
    --counter;
  }
}

void FileDescriptor::pushTime(time_t element, std::vector<char> *buffer) {
  long l_element = long(element);
  char longBuffer[8];
  SerializeInt64(longBuffer, l_element);
  for (int i = 0; i < 8; ++i)
  {
    buffer->push_back(longBuffer[i]);
  }
}

void FileDescriptor::pushPermission(char (&element)[2], std::vector<char> *buffer) {
  for (int i = 0; i < 2; i++) {
    if (element[i]) {
      buffer->push_back(element[i]);
    }
  }
}

void FileDescriptor::SerializeInt32(char (&buf)[4], int val)
{
  for (int i = 3; i >= 0; --i)
  {
    buf[i] = val & 255;
    val = val >> 8;
  }
}

void FileDescriptor::SerializeInt64(char (&buf)[8], long val)
{
  for (int i = 7; i >= 0; --i)
  {
    buf[i] = val & 255;
    val = val >> 8;
  }
}

int32_t FileDescriptor::ParseInt32(const char (&buf)[4])
{
  int val = 0;
  for (int i = 0; i < 4; i++)
  {
    val = val << 8;
    val = val | buf[i];
  }
  return val;
}

bool FileDescriptor::updateUserPermission(int newPermission) {
  //less significant byte
  int lessSignificantByte = atoi((char*)this->permissions[0]);
  //most significant byte
  int mostSignificantByte = atoi((char*)this->permissions[1]);
  int updatedLessSignificantByte = 0;
  int updatedMostSignificantByte = 0;
  bool status = EXIT_ERROR;

  switch (newPermission)
  {
  case R_PERMISSION:
    updatedMostSignificantByte = mostSignificantByte << 2;
    updatedMostSignificantByte = updatedMostSignificantByte | R_PERMISSION;
    updatedMostSignificantByte = updatedMostSignificantByte >> 2;
    this->permissions[1] = (char)updatedMostSignificantByte;
    status = SUCCESS;
    break;
  
  case W_PERMISSION:
    updatedLessSignificantByte = lessSignificantByte >> 6;
    updatedLessSignificantByte = updatedLessSignificantByte | W_PERMISSION;
    updatedLessSignificantByte = updatedLessSignificantByte << 6;
    this->permissions[0] = (char)updatedLessSignificantByte;
    status = SUCCESS;
    break;

  case X_PERMISSION:
    updatedLessSignificantByte = lessSignificantByte >> 6;
    updatedLessSignificantByte = updatedLessSignificantByte | X_PERMISSION;
    updatedLessSignificantByte = updatedLessSignificantByte << 6;
    this->permissions[0] = (char)updatedLessSignificantByte;
    status = SUCCESS;
    break;
  
  case DISSABLE_ALL:
    updatedMostSignificantByte = updatedMostSignificantByte & DISSABLE_ALL;
    updatedLessSignificantByte = updatedLessSignificantByte & DISSABLE_ALL;
    this->permissions[0] = (char)updatedLessSignificantByte;
    this->permissions[1] = (char)updatedMostSignificantByte;
    status = SUCCESS; 
  
  case ENABLE_RWX:
    updatedMostSignificantByte = updatedMostSignificantByte | ENABLE_RWX;
    // ver si esto es necesario, al final desecha los 2 bits de de mas
    // pero para asegurarnos que el resto sea 000
    updatedMostSignificantByte = updatedMostSignificantByte >> 2;
    updatedLessSignificantByte = updatedLessSignificantByte >> 6;
    updatedLessSignificantByte = updatedLessSignificantByte | ENABLE_RWX;
    updatedLessSignificantByte = updatedLessSignificantByte << 6;
    this->permissions[0] = (char)updatedLessSignificantByte;
    this->permissions[1] = (char)updatedMostSignificantByte;
  default:
    break;
  }
}

bool FileDescriptor::updateGroupPermission(int newPermission) {
  return true;
}

bool FileDescriptor::updateAllPermission(int newPermission) {
  return true;
}