#include <iostream>
#include <stdlib.h>

#include "FileDescriptor.h"
#include "DirectoryTree.h"

const int storage_size = 50000;

class FileSystem
{
private:
	DirectoryTree DirectoryTree;
	char storage[storage_size];
	std::string directory;
	std::string activeFolder;
	std::string usuario;
	int *fat;

public:
	FileSystem();
	bool verificarPermisos(std::string file);
	int solicitarEspacio();
	int write(char *data, std::string file, std::string user);
	bool execute(std::string file, std::string user);

	//REQUIERE: carpeta actual
	char *list();
	bool changeFolder(std::string folder);
	bool upFolder();
	bool create(std::string file, std::string user);
	void read(std::string file, std::string user);
	int append(char *data, std::string file, std::string user);
};