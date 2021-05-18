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
    Setea y corrige la direccion en bloques para el root
    y genera el primer directory entry
*/
void Storage::setRoot()
{
    //Address correction
    this->rootAddress = endOfTableAddress / clusterSize;
    if (endOfTableAddress % clusterSize != 0)
    {
        ++rootAddress;
    }

    //Setting the first DirectoryEntry
    FileDescriptor root = FileDescriptor();
    writeDescriptor(root, rootAddress);
}

std::vector<int>* Storage::allocateSpace(int space){
    std::vector<int> * availableSpace;
    int resvInclusters = space / clusterSize;
    for(int i = 0; i < this->totalClusters; i++){
        if(FAT[i].isEmpty()){
            availableSpace->push_back(i);
            if (resvInclusters == 0){
                break;
            }
        }
    }
    if(space != availableSpace->size()){
        return NULL;
    }
    return availableSpace;
}

int Storage::writeDescriptor(FileDescriptor fileDesc, int pos){
    std::vector<int> * availableSpace;
    availableSpace = allocateSpace(DESCRIPTOR_SIZE);
    //Terminar de crear mañana que no aguanto la mano
    return 0;
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
    this->storage = new int[this->diskSize];
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
    this->endOfTableAddress = 24 + FATEntry * totalClusters;
    this->rootAddress = endOfTableAddress;
    this->storage = new int[this->diskSize];
    fillReservedRegion();
    createFAT();
    setRoot();
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
    for (int i = 0; i < this->clusterSize; i += this->blockSize)
    {
        this->storage[(i + (this->clusterSize * index))] = block[i];
    }
}

/*
Retorna un char array (Cluster) de la memoria virtual del indice especificado
*/
char *Storage::readCluster(int clusterId)
{
    char buffer[this->clusterSize];
    for (int i = 0; i < this->clusterSize; i += this->blockSize)
    {
        buffer[i] = this->storage[(i + (this->clusterSize * clusterId))];
    }
    return buffer;
}

/*
Sobrecarga de operadores para poder imprimir un objeto de tipo Storage
*/
std::ostream &operator<<(std::ostream &out, const Storage &storage)
{
    out << "\n\n"
        << "                      DISK STATUS" << std::endl;
    out << "----------------------------------------------------" << std::endl;
    out << "Disk Size in bytes:           " << storage.diskSize << std::endl;
    out << "Disk id:                      " << storage.diskNumber << std::endl;
    out << "Block Size in bytes:          " << storage.blockSize << std::endl;
    out << "Blocks in cluster:            " << storage.clusterBlocks << std::endl;
    out << "Total number of clusters:     " << storage.totalClusters << std::endl;
    out << "Cluster size:                 " << storage.clusterSize << std::endl;
    out << "Root Address:                 " << storage.rootAddress << std::endl;
    out << "----------------------------------------------------"
        << "\n\n"
        << std::endl;
    return out;
}

/*
Imprime la informacion del storage
*/
void Storage::status()
{
    std::cout << this;
}