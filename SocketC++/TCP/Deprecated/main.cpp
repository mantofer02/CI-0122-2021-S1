#include "client.h"
#include "server.h"

int main(int argc, char** argv) {
  if (argc > 1) {
    std::string str(argv[1]);
    if (str == "Server") {
      std::cout << "Creating Server" << std::endl;
      Server myServer;
    } else {
       std::cout << "Creating Client" << std::endl;
       Client myClient;
    }
  }
}