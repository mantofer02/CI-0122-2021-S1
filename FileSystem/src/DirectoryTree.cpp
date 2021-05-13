#include "../include/DirectoryTree.h"
#include <sstream>
#include <iostream>

// Node Section
DirectoryTree::File ::File(FileDescriptor fileDescriptor) {
  this->fileDescriptor = fileDescriptor;
}

DirectoryTree::File ::~File() {
}

DirectoryTree::File *DirectoryTree::File::getChild(std::string name) {
  File *file = NULL;
  for (auto i = this->children.begin(); i != this->children.end(); i++) {
		File *tmp = *i;
		if (tmp->fileDescriptor.name == name) {
			file = *i;
		}
	}
	return file;
}

std::vector<DirectoryTree::File *> DirectoryTree::File::getAllChilds() {
	return this->children;
}

bool DirectoryTree::File::appendChild(FileDescriptor fileDescriptor) {
	this->children.push_back(new File(fileDescriptor));
}

bool DirectoryTree::File ::addFile(File *file) {
}

FileDescriptor DirectoryTree::File ::readFile() {
	return this->fileDescriptor;
}

bool DirectoryTree::File ::updateFile(File *file) {}

bool DirectoryTree::File ::deleteFile() {}

//
//Tree Section
//

std::vector<std::string> splitPath(std::string path) {
	std::vector<std::string> localPath;
	std::string segment;
	std::stringstream ssPath;
	ssPath << path;
	while (std::getline(ssPath, segment, '/')) {
		localPath.push_back(segment);
	}
	return localPath;
}

DirectoryTree::File *DirectoryTree::traverseRecursive(File *node,
std::vector<std::string> path) {
	std::string local = path.front();
	if (local == node->readFile().name) {
		if (path.size() <= 1) {
			return node;
		} else {
			path.erase(path.begin());
			local = path.front();
			File *next = node->getChild(local);
			if (next) {
				return traverseRecursive(next, path);
			}
		}
	}
	return NULL;
}

DirectoryTree::File *DirectoryTree::traverseTree(File *node, std::string path) {
	std::vector<std::string> localPath;
	localPath = splitPath(path);
	File *root = node;

	return traverseRecursive(node, localPath);
}

DirectoryTree::DirectoryTree() {
	this->root = NULL;
}

DirectoryTree::~DirectoryTree() {}

bool DirectoryTree::createFileDescriptor(std::string path,
FileDescriptor fileDescriptor) {
	bool success = false;
	if (this->root) {
		File *node = traverseTree(root, path);
		if (node) {
			node->appendChild(fileDescriptor);
			success = true;
		}
	} else {
		this->root = new File(fileDescriptor);
		success = true;
	}
	return success;
}

FileDescriptor DirectoryTree::readFileDescriptor(std::string path) {}

bool DirectoryTree::updateFileDescriptor(std::string path, FileDescriptor fileDescriptor) {}

bool DirectoryTree::removeFileDescriptor(std::string path) {}

void DirectoryTree::traverse(File *nodo) {
	if (nodo != NULL) {
		auto childs = nodo->getAllChilds();
		std::cout << nodo->readFile().name << std::endl;

		std::cout << "Hijos" << std::endl;
		for (auto i = childs.begin(); i != childs.end(); i++) {
			File* tmp = *i;
			std::cout << tmp->readFile().name << std::endl;
		}
		std::cout << std::endl;
		for (auto i = childs.begin(); i != childs.end(); i++) {
			traverse(*i);
		}
	}
}

void DirectoryTree::traverse() {
	traverse(this->root);
}
