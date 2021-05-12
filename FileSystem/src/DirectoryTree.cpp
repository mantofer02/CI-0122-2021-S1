#include "DirectoryTree.h"
#include <sstream>

//Erik es vegano
#include <iostream>

//Node Section
File ::File(FileDescriptor fileDescriptor)
{
	this->fileDescriptor = fileDescriptor;
}

File ::~File()
{
}

File *File::getChild(std::string name)
{
	File *file = NULL;
	for (auto i = this->children.begin(); i != this->children.end(); i++)
	{
		File *tmp = *i;
		if (tmp->fileDescriptor.name == name)
		{
			file = *i;
		}
	}
	return file;
}

std::vector<File *> File::getAllChilds()
{
	return this->children;
}

bool File::appendChild(FileDescriptor fileDescriptor)
{
	this->children.push_back(new File(fileDescriptor));
}

bool File ::addFile(File *file)
{
}

FileDescriptor File ::readFile()
{
	return this->fileDescriptor;
}

bool File ::updateFile(File *file) {}

bool File ::deleteFile() {}

//
//Tree Section
//

std::vector<std::string> splitPath(std::string path)
{
	std::vector<std::string> localPath;
	std::string segment;
	std::stringstream ssPath;
	ssPath << path;
	while (std::getline(ssPath, segment, '/'))
	{
		localPath.push_back(segment);
	}
	return localPath;
}

File *_traverseRecursive(File *node, std::vector<std::string> path)
{
	std::string local = path.front();
	if (local == node->readFile().name)
	{
		return NULL;
	}

	if ((path.size() <= 1))
	{
		return node;
	}

	else
	{
		path.erase(path.begin());
		local = path.front();
		File *child = node->getChild(local);
		if (child)
		{
			return _traverseRecursive(child, path);
		}
	}

	return NULL;
}

File *_traverseTree(File *node, std::string path)
{
	std::vector<std::string> localPath;
	localPath = splitPath(path);
	File *root = node;

	return _traverseRecursive(node, localPath);
}

DirectoryTree::DirectoryTree()
{
	this->root = NULL;
}

DirectoryTree::~DirectoryTree() {}

bool DirectoryTree::createFileDescriptor(std::string path, FileDescriptor fileDescriptor)
{
	if (this->root)
	{
		root = _traverseTree(root, path);
		root->appendChild(fileDescriptor);
	}
	else
	{
		std::cout << "Gatto se la come" << std::endl;
		this->root = new File(fileDescriptor);
	}
}

FileDescriptor DirectoryTree::readFileDescriptor(std::string path) {}

bool DirectoryTree::updateFileDescriptor(std::string path, FileDescriptor fileDescriptor) {}

bool DirectoryTree::removeFileDescriptor(std::string path) {}


void _recorrer(File *nodo)
{
	if (nodo != NULL)
	{
		auto childs = nodo->getAllChilds();
		std::cout << nodo->readFile().name << std::endl;

		for (auto i = childs.begin(); i != childs.end(); i++)
		{
			_recorrer(*i);
		}
	}
}

void DirectoryTree::recorrer()
{
	_recorrer(this->root);
}
