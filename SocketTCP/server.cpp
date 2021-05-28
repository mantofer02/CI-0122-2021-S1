#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
  //we are going to send data
  char server_buffer[256] = "Hello from server";

  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address; 
  server_address.sin_family = AF_INET;
  // port we know the OS wont use
  server_address.sin_port = htons(9002);
  // any address for local machine
  server_address.sin_addr.s_addr = INADDR_ANY; 
  
  // bind our socket to our IP and port
  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  // second parameter is how many sockets can it listen
  listen(server_socket, 1);

  // 2 way connection 
  int client_socket = accept(server_socket, NULL /*Structure to know 
  from where the client is connecting*/, NULL);

  send(client_socket, server_buffer, sizeof(server_buffer), 0);

  close(server_socket);

  return 0;
}