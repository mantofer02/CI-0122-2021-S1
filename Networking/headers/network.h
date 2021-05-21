#ifndef NETWORK_H
#define NETWORK_H
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#define PORT 8080

class Server
{
private:
    std::string messageBuffer;

public:
    Server();
    bool run();
};

class Client
{
private:
    int socket_descriptor;
    char messageBuffer[1024];
    struct sockaddr_in serv_addr;

public:
    Client();
    bool connectSocket();
    bool sendMessage(void * message);
    bool readMessage();
};
#endif