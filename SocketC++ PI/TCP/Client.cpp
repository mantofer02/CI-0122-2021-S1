#include "Client.h"

Client::Client() {
  // this->buffer = new char[500];
  char client_buffer[500];
  this->network_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  this->socket_address.sin_family = AF_INET;
  this->socket_address.sin_port = htons(9002);
  this->socket_address.sin_addr.s_addr = INADDR_ANY;

  this->connection_status = connect(this->network_socket, (struct sockaddr *) &this->socket_address, sizeof(this->socket_address));

  if (this->connection_status == 0) {
    std::cout << "Client connected" << std::endl;
  } else {
    std::cout << "Connection error" << std::endl;
  }
  int status = recv(this->network_socket, &client_buffer, sizeof(client_buffer), 0);
  std::cout << status << " SIZE" << std::endl;

  std::string message(client_buffer);
  if (!this->connection_status) {
    std::cout << message << std::endl;
  }

  close(network_socket);
}