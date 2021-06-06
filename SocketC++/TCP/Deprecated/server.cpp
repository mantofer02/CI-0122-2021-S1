#include "server.h"


Server::Server() {
  this->file = fopen("file.txt", "r");
  fgets(this->file_data, 1024, this->file);
  char server_buffer[2048] = "[HEADER: INFO OK]";
  strcat(server_buffer, this->file_data);

  this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_port = htons(PORT);
  this->server_address.sin_addr.s_addr = INADDR_ANY; 
  
  bind(this->server_socket, (struct sockaddr *) &this->server_address, sizeof(this->server_address));
  listen(server_socket, 5);
  
  while (1) {
    this->client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, server_buffer, sizeof(server_buffer), 0);
    close(client_socket);
  }
}