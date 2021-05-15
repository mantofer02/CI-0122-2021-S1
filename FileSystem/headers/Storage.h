#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>

//Reserved space Offset en bytes
#define resvdSize 20
#define kb 1024 * 8

//Size of 32bit integer en bytes para ez parse
#define i32Bs
class Storage
{
private:
    int diskSize;       //Tamano del disco en kbs
    int diskNum;        //NumID del disco
    int blockSize;      //Cantidad de bytes en un block
    int clusterBlocks;  //Numero de blocks por cluster  
    int totalClusters;  //Numero total de clusters
    int rootAddress;    //Direccion del FIL root
    int* storage;       //The Virtrual Memory Storage

    void SerializeInt32(char (&buf)[4], int32_t val);
    int32_t ParseInt32(const char (&buf)[4]);
    void writeIntToMemory(int num, int pos);
    void fillReservedRegion();

public:
    Storage();
    Storage(int diskNum, int diskSize, int blockSize, int clusterBlocks);
    ~Storage();
    void loadDiskImage(std::ifstream diskImage);
    void createDiskImage(std::ofstream* diskImage);

};

#endif