---
tags: Redes
title: Trabajo Sockets
---
### Marco Ferraro B82957
## Trabajo Sockets
## Ejecución de Programa
* Archivo de Texto: 
![](https://i.imgur.com/lPEWpbo.png)


* Salida:
    * Server:
    ![](https://i.imgur.com/eQaG11Z.png)
    * Client:
    ![](https://i.imgur.com/Xu3r0Mn.png)

Para entablar esta comunicación bidireccional de sockets mediante protocolo TCP, se uso [este vídeo](https://www.youtube.com/watch?v=LtXEMwSG5-8&t=456s) y la [documentación oficial de c](https://devdocs.io/)

### Diseño de implementación.
Se establecio una comunicación server-client, dónde el server abre un archivo de texto y le manda la información txt de este archivo al cliente por medio de sockets.

```
struct sockaddr_in server_address; 
server_address.sin_family = AF_INET;
server_address.sin_port = htons(9002);
server_address.sin_addr.s_addr = INADDR_ANY; 
```
Esta estructura de `sockaddr_in` poseé la misma inicialización en los 2 programas. 

> An IP socket address is defined as a combination of an IP
interface address and a 16-bit port number.  The basic IP protocol does not supply port numbers, they are implemented by higher level protocols like udp(7) and tcp(7).

Al usar el bind, los 2 sockets van a acceder a la info de esta estructura, al puerto 9002 de la máquina local.