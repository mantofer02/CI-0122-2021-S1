#include "FileDescriptor.h"

FileDescriptor::FileDescriptor()
{
    this->name = "";
    this->id = 0;
    this->type = "";
    this->size = 0;
    this->username = "";
    this->address = -1;
    for (int i = 0; i < 10; ++i)
    {
        this->permissions[i] = false;
    }
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

std::vector<char> FileDescriptor::serialize()
{
    std::vector<char> buffer;
    pushString(this->name, NAME_SIZE, &buffer);
    pushInteger(this->id, ID_SIZE, &buffer);
    pushString(this->type, TYPE_SIZE, &buffer);
    //permissions
    pushInteger(this->size, FILE_SIZE, &buffer);
    pushString(this->username, USERNAME_SIZE, &buffer);
    //time
    pushInteger(this->address, ADDRESS_SIZE, &buffer);
    return buffer;
}

void FileDescriptor::pushInteger(int element, int counter, std::vector<char> *buffer)
{
    char intBuffer[4];
    SerializeInt32(intBuffer,element);
    for(int i = 0; i < 4; ++i)
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