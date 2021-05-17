#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>

//Reserved space Offset en bytes
#define resvdSize 24

//Bytes per FAT Entry
#define FATEntry 5
struct Entry
{
    char empty;
    int direction;

    void setEntry(char isEmpty, int direction);
    bool isEmpty();
    int getDirection();
};

class Storage
{
private:
    int diskSize;      //Tamano del disco en kbs
    int diskNum;       //NumID del disco
    int blockSize;     //Cantidad de bytes en un block
    int clusterBlocks; //Numero de blocks por cluster
    int totalClusters; //Numero total de clusters
    int rootAddress;   //Direccion del FIL root

    //Secciones que no se incluyen en resv
    Entry *FAT;
    int *storage; //The Virtrual Memory Storage

    void SerializeInt32(char (&buf)[4], int val);
    int32_t ParseInt32(const char (&buf)[4]);
    void writeIntToMemory(int num, int pos);
    int readIntFromMemory(int pos);
    void fillReservedRegion();
    void createFAT();
    void createRoot();

public:
    Storage();
    Storage(std::ifstream *diskImage);
    Storage(int diskNum, int diskSize, int blockSize, int clusterBlocks);
    ~Storage();
    void createDiskImage(std::ofstream *diskImage);
    void loadDiskImage(std::ifstream *diskImage);
    void writeCluster(char *block);
    char *readCluster(int clusterId);
    void status();
};

#endif