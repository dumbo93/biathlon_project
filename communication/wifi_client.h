#ifndef WIFI_CLIENT_H_
#define WIFI_CLIENT_H_


int WIFI_init( void );
int WIFI_create_socket( void );
void WIFI_close_socket( int socket_desc );
void WIFI_get_connection( int socket_desc );
int WIFI_send_data( int socket_desc);
int WIFI_receive_data( int socket_desc );



#endif 