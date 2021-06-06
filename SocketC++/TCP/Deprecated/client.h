#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Client {
  private:
    char buffer[256];
    int network_socket;
    struct sockaddr_in server_address;
    int connection_status;

  public:
    Client();
};

#endif