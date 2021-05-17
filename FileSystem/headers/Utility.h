#ifndef UTILITY_H
#define UTILITY_H
#include <bitset>
#include <iostream>
#include <fstream>
#include <ostream>

/* 
Serialization
*/
class Utility
{
public:
  void SerializeInt32(char (&buf)[4], int val)
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
  int32_t ParseInt32(const char (&buf)[4])
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
    Deserialization
  */
};
#endif