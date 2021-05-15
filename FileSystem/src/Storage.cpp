#include <Storage.h>
#include <cstring>

/*
A esta funcion se le pasan un char[4] y un int
y convierte el int en los 4 chars
Esto se puede por la forma en que se usan los bits
a nivel de procesador
*/
void Storage::SerializeInt32(char (&buf)[4], int32_t val)
{
    std::memcpy(buf, &val, 4);
}

/*
A esta funcion se le pasan un char[4] y un int
y convierte el int en los 4 chars
Esto se puede por la forma en que se usan los bits
a nivel de procesador
*/
int32_t Storage::ParseInt32(const char (&buf)[4])
{
    int32_t val;
    std::memcpy(&val, buf, 4);
    return val;
}

void Storage::writeIntToMemory(int num, int pos)
{
    char temp[4];
    SerializeInt32(temp, num);
    for (int i = 0; i < 4; i++)
    {
        this->storage[pos + i] = temp[i];
    }
}

void Storage::fillReservedRegion()
{
    writeIntToMemory(this->diskNum, 0);
    writeIntToMemory(this->blockSize, 4);
    writeIntToMemory(this->clusterBlocks, 8);
    writeIntToMemory(this->totalClusters, 12);
    writeIntToMemory(this->rootAddress, 16);
}

Storage::Storage(int diskSize, int diskNum, int blockSize, int clusterBlocks)
{
    this->diskSize = diskSize;
    this->diskNum = diskNum;
    this->blockSize = blockSize;
    this->clusterBlocks = clusterBlocks;
    this->totalClusters = (diskSize * kb) / (clusterBlocks * blockSize);  
    this->rootAddress = totalClusters * 32;
    this->storage = new int[diskSize * kb];

    fillReservedRegion();
}

Storage::~Storage()
{
    delete this->storage;
}

void Storage::loadDiskImage(std::ifstream diskImage)
{
    
}

void Storage::createDiskImage(std::ofstream *diskImage)
{
    for (int i = 0; i < this->diskSize * kb; i++)
    {
        *diskImage << this->storage[i];
    }
}