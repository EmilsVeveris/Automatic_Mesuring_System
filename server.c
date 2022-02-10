#include <stdio.h> 
#include "socket.h"


int main()
{
    int sock;
    int port = 1234;
    char* ip = "127.0.0.1";
    char check;
    char* c = "c";
    char response[256];
    server_prg(ip, port, &sock);
    scanf("%c", &check);
    
    
    close_socket(&sock);
    return 1;
}
        
        
