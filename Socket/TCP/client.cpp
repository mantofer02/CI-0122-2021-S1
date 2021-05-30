#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  //data
  char buffer[256];
  // holds the socket descriptor
  // SOCK_STREAM = Conection Socket
  // 0 = Default Protocol = TCP
  int network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // structure describing an Internet socket address
  struct sockaddr_in server_address;

  //knows what type of address is working to
  server_address.sin_family = AF_INET;

  // port we know the OS wont use
  server_address.sin_port = htons(9002);
  
  // any address for local machine
  server_address.sin_addr.s_addr = INADDR_ANY; 
  
  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, 
  sizeof(server_address));
  if (connection_status == 0) {
    std::cout << "Socket Connected" << std::endl;
  } else {
    std::cout << "Connection Error" << std::endl;
  }
  recv(network_socket, &buffer, sizeof(buffer), 0 /*Flags parameter*/);

  for (int i = 0; i < 256; i++) {
    std::cout << buffer[i];
  }
  std::cout << std::endl;
  close(network_socket);
  return 0;
}