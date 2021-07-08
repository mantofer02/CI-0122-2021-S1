#ifndef Panagrama_H
#define Panagrama_H

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 512

struct Panagrama {
  int opcode;
  int size;
  char data[BUFFER_SIZE];
};

Panagrama newPanagrama(int opcode, int size, char *data){
  Panagrama datagrama;
  datagrama.opcode = opcode;
  datagrama.size = size;
  memcpy(datagrama.data, data, BUFFER_SIZE);
}

void serialize(Panagrama *datagrama, char data[BUFFER_SIZE]){
  memcpy(data, datagrama, sizeof(Panagrama));
}

void deserialize(Panagrama *datagrama, char data[BUFFER_SIZE]){
  memcpy(datagrama, data, sizeof(Panagrama));
}

#endif
