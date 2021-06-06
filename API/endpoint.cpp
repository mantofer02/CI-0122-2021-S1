#include "endpoint.h"

Endpoint::Endpoint() {
  // intended to run on local machine
  // change this
  int port = 9002;
  this->max_connections = MAX_CONNECTIONS;
  this->network_socket = socket(AF_INET, SOCK_STREAM, 0);
  this->socket_address.sin_family = AF_INET;
  this->socket_address.sin_port = htons(port);
  this->socket_address.sin_addr.s_addr = INADDR_ANY;
  this->connection_status = connect(network_socket, (struct sockaddr *) &socket_address, sizeof(socket_address));

  std::cout << this->connection_status << std::endl;
  if (this->connection_status == 0) {
    std::cout << "INIT AS CLIENT" << std::endl;
    this->operation = RECEIVE;
    initAsClient();
  } else {
    std::cout << "INIT AS SERVER" << std::endl;
    this->operation = SEND; 
    initAsServer();
  }

}
Endpoint::~Endpoint() {}
int Endpoint::initAsServer() {
  int client_socket;
  bind(this->network_socket, (struct sockaddr *) &this->socket_address, sizeof(this->socket_address));
  listen(this->network_socket, this->max_connections);
  bool go = true;
  while (go) {
    client_socket = accept(network_socket, NULL, NULL);
    switch (this->operation)
    {
    case RECEIVE:
      go = receiveEndpoint(this->buffer);
      break;
    case SEND:
      go = sendEndpoint(client_socket, this->buffer);
    default:
      break;
    }
    close(client_socket);
  }
}

int Endpoint::initAsClient() {
  int x;
  switch (this->operation)
  {
  case SEND:
    x = 1;
    break;
  case RECEIVE:
    receiveEndpoint(this->buffer);
  default:
    break;
  }
}
bool Endpoint::sendEndpoint(int client_socket, char* buffer) {
  buffer = "HELLO FROM SERVER";
  send(client_socket, buffer, sizeof(buffer), 0);
  // gotta change it
  return true;
}
bool Endpoint::receiveEndpoint(char* buffer) {
  recv(this->network_socket, &buffer, sizeof(buffer), 0);
  std::cout << "  Message received" << std::endl;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    std::cout << buffer[i];
  }
  return true;
}