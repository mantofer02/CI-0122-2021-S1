#include <Storage.h>

//Seccion de entradas en la tabla FAT
void Entry::setEntry(char isEmpty, int address)
{
  this->address = address;
  this->empty = isEmpty;
}

/*
Obtiene el valor de verdad si el entry esta vacio
*/
bool Entry::isEmpty()
{
  return empty;
}

/*
Obtiene la direccion de un entry
*/
int Entry::getAddress()
{
  return address;
}

/*
A esta funcion se le pasa un numero y la posicion de memoria en que lo quiere almacenar
es unicamente para guardar ints
*/
void Storage::writeIntToMemory(int number, int index)
{
  Utility myUtility;
  char temp[4];
  myUtility.SerializeInt32(temp, number);
  for (int i = 0; i < 4; ++i)
  {
    this->storage[index + i] = temp[i];
  }
}

/*
Lee un int de memoria dado un indice
*/
int Storage::readIntFromMemory(int index)
{
  Utility myUtility;
  char temp[4];
  for (int i = 0; i < 4; i++)
  {
    temp[i] = this->storage[index + i];
  }
  return myUtility.ParseInt32(temp);
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
  writeIntToMemory(this->diskNumber, 4);
  writeIntToMemory(this->blockSize, 8);
  writeIntToMemory(this->clusterBlocks, 12);
  writeIntToMemory(this->totalClusters, 16);
  writeIntToMemory(this->rootAddress, 20);
}

/*
Llena los clusters en todo el storage con valores enteros por defecto(inicializa)
*/
void Storage::setDefaultClusters()
{
  for (int i = reservedSize; i <= this->totalClusters; i += FATEntry)
  {
    this->storage[i] = false;
    writeIntToMemory(-1, i + 1);
  }
}

/*
Escribe los valores por defecto de las entradas en la tabla fat (-1)
*/
void Storage::initializeEntries(Entry *FAT)
{
  for (int i = 0; i < this->totalClusters; ++i)
  {
    FAT[i].setEntry(false, -1);
  }
}

/*
Este metodo crea la tabla FAT dentro de memoria
*/
void Storage::createFAT()
{
  FAT = new Entry[this->totalClusters];
  setDefaultClusters();
  initializeEntries(FAT);
}

/*
Constructor por defecto
*/
Storage::Storage()
{
  this->diskSize = 0;
  this->diskNumber = 0;
  this->blockSize = 0;
  this->clusterBlocks = 0;
  this->totalClusters = 0;
  this->clusterSize = 0;
  this->rootAddress = 0;
  this->storage = new int[diskSize];
}

/*
Constructor que genera un objeto Storage a partir de un archivo
*/
Storage::Storage(std::ifstream *diskImage)
{
    loadDiskImage(diskImage);
}

/*
Obtiene el id del bloque raiz
*/
int Storage::getRootBlock()
{
}

/*
Este constructor crea un Storage a partir de
Tamaño del disco en Kilobytes
Numero identificador de disco
tamaño del block en bits
cantidad de blocks en el cluster
*/
Storage::Storage(int diskSize, int diskNumber, int blockSize, int clusterBlocks)
{
  this->diskSize = diskSize;
  this->diskNumber = diskNumber;
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
Crea una nueva memoria virtual con una imagen de disco
recibida en parametros
*/
void Storage::loadDiskImage(std::ifstream *diskImage)
{
}

/*
Crea una imagen de disco a partir de la memoria
requiere como parametro el ofstream en que se creara la imagen
*/
void Storage::createDiskImage(std::ofstream *diskImage)
{
  for (int i = 0; i < this->diskSize; ++i)
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
  std::cout << "Disk id:                      " << this->diskNumber << std::endl;
  std::cout << "Block Size in bytes:          " << this->blockSize << std::endl;
  std::cout << "Blocks in cluster:            " << this->clusterBlocks << std::endl;
  std::cout << "Total number of clusters:     " << this->totalClusters << std::endl;
  std::cout << "Cluster size:                 " << this->clusterSize << std::endl;
  std::cout << "Root Address:                 " << this->rootAddress << std::endl;
  std::cout << "----------------------------------------------------"
            << "\n\n"
            << std::endl;
}