#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  // 0 = Default Protocol = TCP
  char buffer[256];
  int network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // structure describing an Internet socket address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY; 
  
  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, 
  sizeof(server_address));
  if (connection_status == 0) {
    std::cout << "Client connected" << std::endl;
  } else {
    std::cout << "Connection error" << std::endl;
  }
  recv(network_socket, &buffer, sizeof(buffer), 0 /*Flags parameter*/);

  if (!connection_status) {
    for (int i = 0; i < 256; i++) {
      std::cout << buffer[i];
    }
  }
  std::cout << std::endl;
  close(network_socket);
  return 0;
}