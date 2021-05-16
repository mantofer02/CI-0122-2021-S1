#include <Storage.h>
#include <iostream>

//Seccion de entradas en la tabla FAT
void Entry::setEntry(char isEmpty, int direction){
    this->direction = direction;
    this->empty = isEmpty;
}

bool Entry::isEmpty(){
    return empty;
}

int Entry::getDirection(){
    return direction;
}

//Seccion de Storage

/*
A esta funcion se le pasan un char[4] y un int
y convierte el int en los 4 chars
Esto se puede por la forma en que se usan los bits
a nivel de procesador
*/
void Storage::SerializeInt32(char (&buf)[4], int val)
{
    for (int i = 3; i >= 0; --i)
    {
        buf[i] = val & 255;
        val = val >> 8;
    }
}

/*
A esta funcion se le pasan un char[4] y crea un int32 a partir de esto
*/
int32_t Storage::ParseInt32(const char (&buf)[4])
{
    int val = 0;
    for (int i = 0; i < 4; i++)
    {
        val = val << 8;
        val = val | buf[i];
    }
    return val;
}

/*
A esta funcion se le pasa un numero y la posicion de memoria en que lo quiere almacenar
es unicamente para guardar ints
*/
void Storage::writeIntToMemory(int num, int pos)
{
    char temp[4];
    SerializeInt32(temp, num);

    for (int i = 0; i < 4; i++)
    {
        this->storage[pos + i] = temp[i];
    }
}

int Storage::readIntFromMemory(int pos)
{
    char temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = this->storage[pos + i];
    }
    return ParseInt32(temp);
}

/*
Con esta funcion se llena la seccion reservada
de los primeros 24 bytes de memoria
toma los atributos de la clase que deberian ser llenados
en el constructor
*/
void Storage::fillReservedRegion()
{
    writeIntToMemory(this->diskSize, 0);
    writeIntToMemory(this->diskNum, 4);
    writeIntToMemory(this->blockSize, 8);
    writeIntToMemory(this->clusterBlocks, 12);
    writeIntToMemory(this->totalClusters, 16);
    writeIntToMemory(this->rootAddress, 20);
}

/*
Este metodo crea la tabla FAT dentro de memoria
*/
void Storage::createFAT()
{
    for (int i = resvdSize; i < totalClusters * FATEntry; i += FATEntry)
    {
        this->storage[i] = false;
        writeIntToMemory(-1, i + 1);
    }
}

/*
Este constructor genera un Storage a partir de un archivo

Storage::Storage(std::ifstream *diskImage)
{
    loadDiskImage(diskImage);
}
*/

/*
Este constructor crea un Storage a partir de
Tamaño del disco en Kilobytes
Numero identificador de disco
tamaño del block en bits
cantidad de blocks en el cluster
*/
Storage::Storage(int diskSize, int diskNum, int blockSize, int clusterBlocks)
{
    this->diskSize = diskSize;
    this->diskNum = diskNum;
    this->blockSize = blockSize;
    this->clusterBlocks = clusterBlocks;
    this->totalClusters = diskSize / (clusterBlocks * blockSize);
    this->rootAddress = resvdSize + (totalClusters * FATEntry); //cambiar para alienar con siguiente bloque
    this->storage = new int[diskSize];

    fillReservedRegion();
    createFAT();
}

//Destruye el almacenamiento para liberar memoria
Storage::~Storage()
{
    delete this->storage;
}

/*
void Storage::loadDiskImage(std::ifstream *diskImage)
{
}
*/

/*
Crea una imagen de disco a partir de la memoria
requiere como parametro el ofstream en que se creara la imagen
*/
void Storage::createDiskImage(std::ofstream *diskImage)
{
    for (int i = 0; i < this->diskSize; i++)
    {
        *diskImage << this->storage[i];
    }
}

/*
Imprime la informacion del storage
*/
void Storage::status()
{
    std::cout << "Disk Size in bytes: " << this->diskSize << std::endl;
    std::cout << "Disk id: " << this->diskNum << std::endl;
    std::cout << "Block Size in bytes: " << this->blockSize << std::endl;
    std::cout << "Blocks in cluster: " << this->clusterBlocks << std::endl;
    std::cout << "Total number of clusters: " << this->totalClusters << std::endl;
    std::cout << "Root Address: " << this->rootAddress << std::endl;
}