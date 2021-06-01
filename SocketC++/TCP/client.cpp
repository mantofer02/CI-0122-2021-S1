#include "client.h"

Client::Client() {
  this->network_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_port = htons(9002);
  this->server_address.sin_addr.s_addr = INADDR_ANY;

  this->connection_status = connect(this->network_socket, (struct sockaddr *) &this->server_address, sizeof(this->server_address));

  if (this->connection_status == 0) {
    std::cout << "Client connected" << std::endl;
  } else {
    std::cout << "Connection error" << std::endl;
  }

  recv(this->network_socket, &this->buffer, sizeof(this->buffer), 0);

  if (!this->connection_status) {
    for (int i = 0; i < 256; i++) {
      std::cout << buffer[i];
    }
  }
  std::cout << std::endl;
  close(network_socket);
}