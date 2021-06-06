#ifndef CLIENT_H
#define CLIENT_H

#include "Network.h"

class Client : public Network {
  private:
    int server_socket;
   
  public: 
    Client();
    Client(struct sockaddr_in socket_address) {}
    bool sendMsg() override { return true; }
    bool recMsg() override { return true; }
};



#endif