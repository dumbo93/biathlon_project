#ifndef WIFI_CLIENT_H_
#define WIFI_CLIENT_H_
#include <arpa/inet.h>

int socket_desc;

int WIFI_init( void );
void WIFI_close_socket( void );
int WIFI_send_data( void );

#endif 
