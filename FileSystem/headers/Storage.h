#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>

//Reserved space Offset en bytes
#define resvdSize 24

//Bytes per FAT Entry
#define FATBlock 5

class Storage
{
private:
    int diskSize;      //Tamano del disco en kbs
    int diskNum;       //NumID del disco
    int blockSize;     //Cantidad de bytes en un block
    int clusterBlocks; //Numero de blocks por cluster
    int totalClusters; //Numero total de clusters
    int rootAddress;   //Direccion del FIL root
    int *storage;      //The Virtrual Memory Storage

    void SerializeInt32(char (&buf)[4], int val);
    int32_t ParseInt32(const char (&buf)[4]);
    void writeIntToMemory(int num, int pos);
    int readIntFromMemory(int pos);
    void fillReservedRegion();
    void createFAT();

public:
    Storage(std::ifstream *diskImage);
    Storage(int diskNum, int diskSize, int blockSize, int clusterBlocks);
    ~Storage();
    void createDiskImage(std::ofstream *diskImage);
    void loadDiskImage(std::ifstream *diskImage);
    void writeCluster(char* block);
    char* readCluster();
    void status();
};

#endif