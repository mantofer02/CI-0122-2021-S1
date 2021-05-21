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
    char messageBuffer[1024];
    int serverSocketDescriptor;
    int connectionSocketDescriptor;
    int addressLength;
    struct sockaddr_in address;

public:
    Server();
    bool run();
    bool sendMessage(void *message);
    void bindSocket();
    void listenForMessages(int timesToListen);
    void acceptConnecton();
    void readFromConnection();
};

class Client
{
private:
    char messageBuffer[1024];
    int clientSocketDescriptor;
    struct sockaddr_in serverAddress;

public:
    Client();
    bool connectSocket();
    bool sendMessage(void *message);
    bool readMessage();
};
#endif