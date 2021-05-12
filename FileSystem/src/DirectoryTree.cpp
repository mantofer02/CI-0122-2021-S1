#include "DirectoryTree.h"

File ::File(FileDescriptor fileDescriptor)
{
	this->fileDescriptor = fileDescriptor;
}

File ::~File()
{
}

bool File::addChildren(File *file)
{
	if (this->fileDescriptor.type != "dir")
	{
		children.push_back(file);
	}
}

bool File::removeChildren(File *file)
{
}

DirectoryTree::DirectoryTree()
{
	this->root = NULL;
}

DirectoryTree::~DirectoryTree() {}

bool DirectoryTree::createFileDescriptor(std::string path, FileDescriptor fileDescriptor)
{
	if(this->root){

	}
	else{
		this->root = new File(fileDescriptor);
	}
}

FileDescriptor DirectoryTree::readFileDescriptor(std::string path) {}

bool DirectoryTree::updateFileDescriptor(std::string path, FileDescriptor fileDescriptor) {}

bool DirectoryTree::removeFileDescriptor(std::string path) {}