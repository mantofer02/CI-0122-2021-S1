#include "Server.h"

Server::Server() {
  char server_buffer[500] = "Hello from Server";
  this->buffer = "Hello From Server";
  this->network_socket =  socket(AF_INET, SOCK_STREAM, 0);
  this->socket_address.sin_family = AF_INET;
  this->socket_address.sin_port = htons(PORT);
  this->socket_address.sin_addr.s_addr = INADDR_ANY;

  bind(this->network_socket, (struct sockaddr *) &this->socket_address, sizeof(this->socket_address));
  listen(network_socket, 5);


  while (1) {
    this->client_socket = accept(network_socket, NULL, NULL);
    std::cout << "Out of queue" << std::endl;
    send(client_socket, server_buffer, sizeof(server_buffer), 0);
    close(client_socket);
  }
}