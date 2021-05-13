#include "../include/FileSystem.h"

FileSystem::FileSystem() {
  this->user = "Luis Carlos";
  this->directory = "PC Directory";
  this->activeFolder = "PC Active Folder";
  this->fat = new int [5];
}

FileSystem::~FileSystem() {
	delete fat;
}
bool FileSystem::checkPermissions(std::string file) {
  return true;
}

int FileSystem::reallocSpace(){
	return 1;
}

int FileSystem::write(char *data, std::string file, std::string user){
	this->user = user;
}

bool FileSystem::execute(std::string file, std::string user) {
	return true;
}

char* FileSystem::list() {
	return "return";
}

bool FileSystem::upFolder() {
	return true;
}

bool FileSystem::create(std::string file, std::string user) {
	return 1;
}

void FileSystem::read(std::string file, std::string user) {

}

int FileSystem::append(char* data, std::string file, std::string user) {
	return 1;
}
