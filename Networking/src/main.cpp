#include "network.h"

int main()
{
    Server *server = new Server();
    Client *client = new Client();
    server->bindSocket();
    server->run();
    client->connectSocket();
    client->sendMessage((void *) 7);
    client->readMessage();
    return 0;
}