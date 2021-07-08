#ifndef SERVER_H
#define SERVER_H

#include "Network.h"

class Server : public Network {
  private:
    int client_socket;
   
  public: 
    Server();
    Server(struct sockaddr_in socket_address) {}
    bool sendMsg() override { return true; }
    bool recMsg() override { return true; }
};

#endif