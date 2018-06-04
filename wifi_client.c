#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <unistd.h>

#include "wifi_client.h"
#include "central_state.h"


int WIFI_init( int socket_desc )
{
	printf("Hello from wifi_init\n");
    	int sendt_data, received_data;
	struct sockaddr_in server;
	
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    	if (socket_desc == -1)
    	{
       	 	printf("Could not create socket\n");
    	}
	
	
	server.sin_addr.s_addr = inet_addr("129.241.154.24");
    	// IP for PC used: 129.241.154.24
	server.sin_family = AF_INET;
    	server.sin_port = htons( 8888 );

    	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
   	{
        	printf("connect error\n");
		return 0;
    	}
     
    	printf("Connected\n");
    	return 1;
}


void WIFI_close_socket( int socket_desc )
{
	close(socket_desc);
}



int WIFI_send_data( int socket_desc )
{
    if( send(socket_desc , &current_value_hex , strlen(&current_value_hex) , 0) < 0)
    {
        printf("Send failed\n");
        return 1;
    }
    printf("Data Sendt %s \n", &current_value_hex);
    return 0;
}

