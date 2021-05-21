#include "network.h"

Server::Server()
{
    int opt = 1;
    this->serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(this->serverSocketDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(PORT);
}

void Server::bindSocket()
{
    bind(this->serverSocketDescriptor, (struct sockaddr *)&address, sizeof(address));
}

void Server::listenForMessages(int timesToListen)
{
    listen(this->serverSocketDescriptor, timesToListen);
}

void Server::acceptConnecton()
{
    this->connectionSocketDescriptor= accept(this->serverSocketDescriptor, (struct sockaddr *)&address, (socklen_t *)&this->addressLength);
}

void Server::readFromConnection()
{
    read(connectionSocketDescriptor, messageBuffer, 1024);
}

bool Server::sendMessage(void * message)
{
    send(this->serverSocketDescriptor , message , sizeof(void *) , 0 );
    std::cout << "Mensaje enviado" << std::endl;
    return true;
}