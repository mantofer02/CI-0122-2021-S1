#include "network.h"

Client::Client()
{
    this->socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
}

bool Client::connectSocket()
{
    if(connect(this->socket_descriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        return false;
    }else
    {
        return true;
    }
}

bool Client::sendMessage(void * message)
{
    send(this->socket_descriptor , message , sizeof(void *) , 0 );
    std::cout << "Mensaje enviado" << std::endl;
    return true;
}

bool Client::readMessage()
{
    read( this->socket_descriptor , messageBuffer, 1024);
    return true;
}