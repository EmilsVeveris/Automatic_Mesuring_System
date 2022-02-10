#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

short close_socket(int* socket);
short client_prg(char* ip, int port, int* Client_socket);
short server_prg(char* ip, int port, int* Server_socket, int client_socket_response);

#endif
