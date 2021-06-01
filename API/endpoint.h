#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <regex>

#define COMMAND_REGEX "(^(<)\\w+(>))"
#define PORT 9002

#define BUFFER_SIZE 256
#define SEND 1
#define RECEIVE 2
#define MAX_CONNECTIONS 5

class Endpoint {
  private:
    int operation;
    char buffer[BUFFER_SIZE];
    int connection_status;
    int network_socket;
    struct sockaddr_in socket_address;
    int max_connections;
  
  public:
    Endpoint();
    ~Endpoint();
    int initAsServer();
    int initAsClient();
    bool sendEndpoint(int client_socket, char* buffer);
    bool receiveEndpoint(char* buffer);

};
#endif
