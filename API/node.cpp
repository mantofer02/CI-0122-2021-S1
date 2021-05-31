#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <regex>

#define COMMAND_REGEX "(^(<)\\w+(>))"

#define PORT 9002
#define AMOUNT_CONNECTIONS 5

/* acts like server */
bool receiveMessage(int network_socket, char* buffer);
bool sendMessage(int network_socket, char* buffer);

int main(void) {
  char buffer[256];
  int network_socket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in socket_address;
  socket_address.sin_family = AF_INET;
  socket_address.sin_port = htons(9002);
  socket_address.sin_addr.s_addr = INADDR_ANY;

  bool go = true;
  int endpoint;
  int connection_status = connect(network_socket,
  (struct sockaddr *) &socket_address, sizeof(socket_address));

  if (connection_status == 0) {
    while (go) {
      go = sendMessage(network_socket, buffer);
    }
  } else {
    bind(network_socket, (struct sockaddr *) &socket_address,
    sizeof(socket_address));

    listen(network_socket, AMOUNT_CONNECTIONS);
    while(go) {
        go = receiveMessage(network_socket, buffer);
    }
  }
}

bool receiveMessage(int network_socket, char* buffer) {
  int result = recv(network_socket, &buffer, sizeof(buffer), 0);
  if (result != -1) {
    std::cout << "MESSAGE RECEIVED" << std::endl;
  } else {
    if (result == -1) {
      std::cout << "RECEIVE ERROR" << std::endl;
    }
  }
  if (buffer == "<exit>") {
    return false;
  } else {
    return true;
  }
}

bool sendMessage(int network_socket, char* buffer) {
  bool go = true;
  char localBuffer[256];
  std::regex reg(COMMAND_REGEX);
  std::string input;
  std::cout << "Enter command" << std::endl;
  std::cin >> input;

  while (!std::regex_match(input.begin(), input.end(), reg)) {
    std::cout << "Not a valid command" << std::endl;
    std::cin >> input;
  }

  if (input == "<exit>") {
    go = false;
  }


  strcpy(localBuffer, input.c_str());
  strcat(buffer, localBuffer);
  int destine_socket = accept(network_socket, NULL, NULL);
  send(destine_socket, buffer, sizeof(buffer), 0);
  close(destine_socket);
  return go;
}
