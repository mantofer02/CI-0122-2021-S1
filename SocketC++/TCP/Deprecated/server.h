#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 9002


class Server {
  private:
    int client_socket;
    int server_socket;
    struct sockaddr_in server_address;
  
    FILE* file;
    char file_data[1024];
    // char server_buffer[2048];
  public: 
    Server();
};
#endif