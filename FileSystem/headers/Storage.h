#ifndef STORAGE_H
#define STORAGE_H
#include <Utility.h>
#define reservedSize 24 //Reserved space Offset en bytes
#define FATEntry 5      //Bytes per FAT Entry
struct Entry
{
    char empty;
    int address;
    void setEntry(char isEmpty, int address);
    bool isEmpty();
    int getAddress();
};

class Storage
{
private:
    int diskSize;       //Tamano del disco en kbs
    int diskNumber;     //NumID del disco
    int blockSize;      //Cantidad de bytes en un block
    int clusterBlocks;  //Numero de blocks por cluster
    int clusterSize;    //tamano de los clusters
    int totalClusters;  //Numero total de clusters
    int rootAddress;    //Direccion del FIL root
    int *storage;       //The Virtrual Memory Storage
    Entry *FAT;         //Secciones que no se incluyen en resv
    
    void writeIntToMemory(int number, int index);
    int readIntFromMemory(int index);
    void fillReservedRegion();
    void initializeEntries(Entry * FAT);
    void setDefaultClusters();
    void createFAT();
    void createRoot();

public:
    Storage();
    Storage(std::ifstream *diskImage);
    Storage(int diskNumber, int diskSize, int blockSize, int clusterBlocks);
    ~Storage();
    int getRootBlock();
    void createDiskImage(std::ofstream *diskImage);
    void loadDiskImage(std::ifstream *diskImage);
    void writeCluster(char *block, int index);
    char * readCluster(int clusterId);
    void status();
    friend std::ostream & operator << (std::ostream &out, const Storage &storage);
};
#endif