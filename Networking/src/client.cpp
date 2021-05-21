#include "network.h"

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *mensaje_prueba = "Mensaje De Prueba";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Fallo en el constructor del socket" << std::endl;
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        std::cout << "Dirección inválida" << std::endl;
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Conexión fallida" << std::endl;
        return -1;
    }
    send(sock , mensaje_prueba , strlen(mensaje_prueba) , 0 );
    std::cout << "Mensaje enviado" << std::endl;
    valread = read( sock , buffer, 1024);
    std::cout << buffer << std::endl;
    return 0;
}