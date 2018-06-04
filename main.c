// include files
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "wifi_client.h"
#include "serial_port.h"
#include "save_data.h"
#include "central_state.h"



int main( int argc, char *argv[] ){
	
	printf("Hello from main\n");
	int connected;
	time_t current_time;
	
	current_time = time(NULL);
	struct tm stime = *localtime(&current_time);
	
	if(current_time == ((time_t)-1))
	{
		printf("failed to obtain the current time.\n");
		return 0;
	}
	init_create_file(stime);
	serial_init();
	connected = WIFI_init();
	
	printf("main: %d\n", socket_desc);
	while(1)
	{
		switch( central_state_get() ){
			case read_serial:
				serial_read();
				break;
				
			case got_value:
				save_data_val( );
				if (connected){
					WIFI_send_data( socket_desc );
				}
				central_state_set( read_serial );
				break;
			default:
				central_state_set( read_serial);
				break;
			}
	}
	
	printf("Closing socket and serial port\n");
	WIFI_close_socket( socket_desc );
	serial_close();

	return 0;
}
