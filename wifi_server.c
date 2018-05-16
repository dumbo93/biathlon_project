// https://www.binarytides.com/socket-programming-c-linux-tutorial/
// Open a socket
// Bind to a address(and port).
// Listen for incoming connections.
// Accept connections
// Read/Send
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#include "wifi_server.h"

int WIFI_init( void )
{
	printf("hello from wifi_init\n");
	int socket_desc;
	int accepted = 0;
	socket_desc = WIFI_create_socket( );
	WIFI_bin_socket( socket_desc);
	printf("WIFI_INIT: bind done\n");
	WIFI_listen( socket_desc );
	printf("WIFI_INIT: listen done\n");
	accepted = WIFI_accept( socket_desc);

	return accepted;
}

int WIFI_create_socket()
{
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    return socket_desc;
}

void WIFI_bin_socket( int socket_desc)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
    	printf("bind failed\n");
	}
	printf("bind done\n");
}


void WIFI_listen( int socket_desc )
{
	listen(socket_desc , 3);
}

int WIFI_accept( int socket_desc)
{
	printf("Waiting for incoming connections...");
	char *message;
	int *new_sock;
	int c, new_socket;
	c = sizeof(struct sockaddr_in);
	struct sockaddr_in client; 
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        printf("Connection accepted\n");
         
        //Reply to the client
        message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
        write(new_socket , message , strlen(message));
         
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        printf("Handler assigned\n");
    }
     
    if (new_socket<0)
    {
        printf("accept failed");
    }
    return 0;
}


void WIFI_write( int new_socket, char *message )
{
	message = "Hello Client , I have received your connection. But I have to go now, bye\n";
	write(new_socket, message, strlen(message));
}

void *connection_handler( void *socket_desc )
{
	int sock = *(int*)socket_desc;
	int read_size;

	char *message, client_message[2000];


	message = "Gratings!\n";
	write(sock, message, strlen(message));

	message = "Its my duty to communicate with you";
	write(sock, message, strlen(message));

	//Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        write(sock , client_message , strlen(client_message));
    }
     
    if(read_size == 0)
    {
        printf("Client disconnected\n\n");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        printf("recv failed\n");
    }
         
    //Free the socket pointer

	free(socket_desc);

	return 0;
}
