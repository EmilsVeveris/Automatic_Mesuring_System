#include "socket.h"


short close_socket(int* socket)
{
    close(*socket);
    return 1;
}
short client_prg(char* ip, int port, int* fd)
{
	struct sockaddr_in serv_addr;				//IPv4 implementacija
		
	printf("IP set to:\t\t\t%s\n", ip);
	
	if((*fd = socket(AF_INET, SOCK_STREAM,0)) < 0){
		perror("*** Create socket!\n");
		return -1;
	}

	//printf("test_1\n");
	//fcntl(*fd, F_SETFL, O_NONBLOCK);  // set to non-blocking
	struct timeval tv;
	tv.tv_sec = 5;  /* 10 Secs Timeout */
	tv.tv_usec = 0;  // Not init'ing this can cause strange errors
	//set read socket timeout as 10 s
	if (setsockopt(*fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval)) !=0)
		perror("setsockopt1");

	//printf("test_2\n");
	//send write to socket timeout as 10 s
	if (setsockopt(*fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval)) != 0)
		perror("setsockopt2");
	
	printf("Socket:\t\t\t\tcreated\n");
	
	serv_addr.sin_family 		= AF_INET;		//adreses tips (AF_INET priek's tcp)
	serv_addr.sin_port 		= htons(port);		//piesleegsanaas osta
	serv_addr.sin_addr.s_addr	= inet_addr(ip); 	//servera IP
	if(connect(*fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ){
		perror("*** Connect\n");
		return -1;
	}

	printf("Connection to server:\t\tOK\n");
	return 1;
}

short server_prg(char* ip, int port, int* server_socket, int client_socket_response)
{     
    char server_message[256] = "you have reached the server!";
    *server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);
    
    bind(*server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(*server_socket, 5);

    client_socket_response = accept(*server_socket, NULL, NULL);
    
    /* send(client_socket_response, server_message, sizeof(server_message), 0);
     char client_response[255] = "C";
     while(1){
         sleep(1);
     recv(client_socket_response, &client_response, sizeof(client_response), 0);
     printf("The client sent the data: %s\n", client_response);
     }*/
    return 1;
}
