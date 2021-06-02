#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"

class Server : public Network {
  private:
    int client_socket;
   
  public: 
    Server();
    Server(struct sockaddr_in socket_address);
    bool sendMsg() override;
    bool recMsg() override;
};
#endif