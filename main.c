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
	//connected = WIFI_init();
	
	//printf("main: %d\n", socket_desc);
	while(1)
	{
		switch( central_state_get() ){
			case wait_for_data:
				if (serial_read()){
					central_state_set(new_data_received);
				}
				break;
				
			case new_data_received:
				serial_new_data();
				save_data_val();
				//if (connected){
					//WIFI_send_data( );
				//}
				break;
				
			case hrm_data_received:
				if (serial_read()){
					if (current_value == '\n'){
						central_state_set(wait_for_data);
						save_data_end();
					}
					else {
						save_data_val();
					}
				}				
				break;
				
			case phy5_data_received:
				if (serial_read()){
					if (current_value == '\n'){
						central_state_set(wait_for_data);
						save_data_end();
					}
					else {
						save_data_val();
					}
				}
				break;
			
			default:
				central_state_set( wait_for_data);
				break;
			}
	}
	
	printf("Closing socket and serial port\n");
	//WIFI_close_socket( socket_desc );
	serial_close();

	return 0;
}
