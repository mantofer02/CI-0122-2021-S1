#include "FileDescriptor.h"

FileDescriptor::FileDescriptor()
{
    this->name = "";
    this->id = 0;
    this->type = "";
    this->size = 0;
    this->username = "";
    this->address = -1;
}
FileDescriptor::FileDescriptor(char *fileDescriptor)
{
}
FileDescriptor::FileDescriptor(std::string name, int id, bool permissions[10], int size, std::string username)
{
    this->name = name;
    this->id = id;
    for (int i = 0; i < 10; ++i)
    {
        this->permissions[i] = permissions[i];
    }
    this->size = size;
    this->username = username;
}
char *FileDescriptor::serialize()
{
}
void FileDescriptor::SerializeInt32(char (&buf)[4], int val)
{
    for (int i = 3; i >= 0; --i)
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