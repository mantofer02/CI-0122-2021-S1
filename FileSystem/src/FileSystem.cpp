
#include "FileSystem.h"

FileSystem::FileSystem()
{
  this->storage = Storage(25 * 1024 * 1024, 0, 64, 2);
}

FileSystem::~FileSystem()
{
  delete FAT;
}

bool FileSystem::checkPermissions(std::string file)
{
  return true;
}

bool FileSystem::checkPermissions(std::string file, int index)
{
  return true;
}

int FileSystem::write(char *data, std::string file, std::string user)
{
  this->user = user;
}

bool FileSystem::execute(std::string file, std::string user)
{
  return true;
}

char *FileSystem::list()
{
  return "return";
}

bool FileSystem::upFolder()
{
  return true;
}

bool FileSystem::create(std::string file, std::string user)
{
  return false;
}

void FileSystem::read(std::string file, std::string user)
{
}

int FileSystem::append(char *data, std::string file, std::string user)
{
  return 1;
}
