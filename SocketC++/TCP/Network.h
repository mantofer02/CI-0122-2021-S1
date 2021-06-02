#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 9002
#define MAX_BUFFER_SIZE 1024

class Network {
  protected:
    struct sockaddr_in socket_address;
    // char buffer[BUFFER_SIZE];
    char* buffer;
    int buffer_size;
    // int client_socket;
    int network_socket;
    int connection_status;
    int operation;

  public:
    Network() {}

    Network(struct sockaddr_in socket_address) {
      this->socket_address = socket_address;
    }

    virtual bool sendMsg()=0;
    virtual bool recMsg()=0;
    char* getData() {
      return buffer;
    }
    
    void setData(char* buffer) {
      if (sizeof(buffer) <= MAX_BUFFER_SIZE) {
        this->buffer_size = sizeof(buffer);
        this->buffer = buffer;
      }
    }

    void printBuffer() {
      for (int i = 0; i < buffer_size; i++) {
        std::cout << buffer[i];
      }
      std::cout << std::endl;
    }

};

#endif