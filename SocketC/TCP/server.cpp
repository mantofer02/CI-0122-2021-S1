#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 9002

int main(void) {
  // Server sends data

  FILE* file = fopen("file.txt", "r");
  char file_data[1024];
  fgets(file_data, 1024, file);

  char server_buffer[2048] = "[HEADER: INFO OK]";
  strcat(server_buffer, file_data);

  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_address; 
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY; 
  
  // bind our socket to our IP and port
  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  listen(server_socket, 5);
  
  
  // 2 way connection
  int client_socket;

  while (1) {
    client_socket = accept(server_socket, NULL /*Structure to know from 
    where the client is connecting*/, NULL);
    send(client_socket, server_buffer, sizeof(server_buffer), 0);
    close(client_socket);
  }

  return 0;
}