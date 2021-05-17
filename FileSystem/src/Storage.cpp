#include <Storage.h>
#include <iostream>

//Seccion de entradas en la tabla FAT
void Entry::setEntry(char isEmpty, int address)
{
    this->address = address;
    this->empty = isEmpty;
}

bool Entry::isEmpty()
{
    return empty;
}

int Entry::getAddress()
{
    return address;
}

//Seccion de Storage

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

    FAT = new Entry[this->totalClusters];
    for (int i = resvdSize; i <= totalClusters; i += FATEntry)
    {
        this->storage[i] = false;
        writeIntToMemory(-1, i + 1);
    }
    for (int i = 0; i < totalClusters; ++i)
    {
        FAT[i].setEntry(false, -1);
    }
}

//Constructor default
Storage::Storage()
{
    this->diskSize = 0;
    this->diskNum = 0;
    this->blockSize = 0;
    this->clusterBlocks = 0;
    this->totalClusters = 0;
    this->clusterSize = 0;
    this->rootAddress = 0;
    this->storage = new int[diskSize];
}

/*
Este constructor genera un Storage a partir de un archivo

Storage::Storage(std::ifstream *diskImage)
{
    loadDiskImage(diskImage);
}
*/

/*
int calucalteRootBlock(){
    int fatFinalEntry = FATEntry * 
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
    this->clusterSize = clusterBlocks * blockSize;
    this->totalClusters = diskSize / clusterSize;
    this->rootAddress = 24 + FATEntry * totalClusters;
    this->storage = new int[diskSize];

    fillReservedRegion();
    createFAT();
}

//Destruye el almacenamiento para liberar memoria
Storage::~Storage()
{
    delete this->storage;
    delete this->FAT;
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
Busca el primer entry vacio en el FAT system y escribe la direccion
del bloque recibido en parametros
*/
void Storage::writeCluster(char *block, int index)
{
    for (int i = 0; i < clusterSize; i += blockSize)
    {
        this->storage[(i + (clusterSize * index))] = block[i];
    }
}

/*
Retorna un char array (Cluster) de la memoria virtual del indice especificado
*/
char *Storage::readCluster(int clusterId)
{
    char buffer[clusterSize];
    for (int i = 0; i < clusterSize; i += blockSize)
    {
        buffer[i] = this->storage[(i + (clusterSize * clusterId))];
    }
    return buffer;
}

/*
Imprime la informacion del storage
*/
void Storage::status()
{
    std::cout << "\n\n"
              << "                      DISK STATUS" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Disk Size in bytes:           " << this->diskSize << std::endl;
    std::cout << "Disk id:                      " << this->diskNum << std::endl;
    std::cout << "Block Size in bytes:          " << this->blockSize << std::endl;
    std::cout << "Blocks in cluster:            " << this->clusterBlocks << std::endl;
    std::cout << "Total number of clusters:     " << this->totalClusters << std::endl;
    std::cout << "Cluster size:                 " << this->clusterSize << std::endl;
    std::cout << "Root Address:                 " << this->rootAddress << std::endl;
    std::cout << "----------------------------------------------------"
              << "\n\n"
              << std::endl;
}