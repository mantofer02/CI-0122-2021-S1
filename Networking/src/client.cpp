#include "network.h"

Client::Client()
{
    this->clientSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
}

bool Client::connectSocket()
{
    if(connect(this->clientSocketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        return false;
    }else
    {
        return true;
    }
}

bool Client::sendMessage(void * message)
{
    send(this->clientSocketDescriptor , message , sizeof(void *) , 0 );
    std::cout << "Mensaje enviado" << std::endl;
    return true;
}

bool Client::readMessage()
{
    read( this->clientSocketDescriptor , messageBuffer, 1024);
    return true;
}