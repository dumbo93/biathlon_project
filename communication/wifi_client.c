// http://www.linuxhowtos.org/C_C++/socket.htm (13. april 2018)
// https://www.binarytides.com/socket-programming-c-linux-tutorial/ (16. april 2018)

// create a socket with socket() system call
// Connect to remote server
// Send some data
// Receive a reply
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include "wifi_client.h"

int WIFI_init( void )
{
	printf("Hello from wifi_init\n");
    int socket_desc = 0;
    //socket_desc = WIFI_create_socket();
    //WIFI_get_connection( socket_desc );
    return socket_desc;
}

int WIFI_create_socket( void )
{
    int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    
    if (socket_desc == -1)
    {
        printf("Could not create socket\n");
    }
    return socket_desc;
}


void WIFI_close_socket( int socket_desc )
{
	close(socket_desc);
}


void WIFI_get_connection( int socket_desc )
{
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr("129.241.154.24");
    // IP for PCen på skolen: 129.241.154.24
	// IP address of google.com: 74.125.235.20 
	server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("connect error\n");
    }
     
    printf("Connected\n");
}


int WIFI_send_data( int socket_desc)
{
    char *message;
	message = "Hello from client\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        printf("Send failed\n");
        return 1;
    }
    printf("Data Send\n");
    return 0;
}

int WIFI_receive_data( int socket_desc )
{
    char server_reply[2000];
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        printf("recv failed\n");
        return 1;
    }
    printf("Reply received\n");
    //printf(server_reply);
    return 0;
}
