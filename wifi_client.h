#ifndef WIFI_CLIENT_H_
#define WIFI_CLIENT_H_
#include <arpa/inet.h>

int WIFI_init( int socket_desc );
void WIFI_close_socket( int socket_desc );
int WIFI_send_data( int socket_desc );

#endif 
