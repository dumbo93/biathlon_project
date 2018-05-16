// include files
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "wifi_client.h"
#include "serial_port.h"
#include "save_data.h"
#include "central_state.h"



int main( int argc, char *argv[] ){
	
	//int socket_desc = 0;
	char received_val = 0;
	printf("Hello from main\n");
	time_t current_time;
	
	current_time = time(NULL);
	struct tm stime = *localtime(&current_time);
	
	if(current_time == ((time_t)-1))
	{
		printf("failed to obtain the current time.\n");
		return 0;
	}
	serial_init();
	init_make_file(stime);
	
	//int socket_desc;
	
	//socket_desc = WIFI_init(socket_desc);
	//printf("%d\n", socket_desc);
	
	central_state_set( read_serial );
	
	while(1)
	{
		switch( central_state_get() ){
			case read_serial:
				received_val = serial_read();
				break;
				
			case got_value:
				save_data_val( received_val );
				// send value on wifi
				central_state_set( read_serial );
				break;
			default:
				central_state_set( read_serial);
			}
	}
	
	printf("Closing socket and serial port\n");
	//WIFI_close_socket( socket_desc );
	serial_close();

	return 0;
}
