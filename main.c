// include files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "serial_port_phy5.h"
#include "serial_port_hrm.h"
#include "save_data.h"
#include "central_state.h"
#include "sensor_id.h"




int main( int argc, char *argv[] ){
	
	printf("Hello from main\n");
	time_t current_time;
	uint8_t data_len  = 0;
	
	const uint8_t	data_len_hrm 	= 2;
	const uint8_t	data_len_phy5	= 20;
	
	current_time = time(NULL);
	struct tm stime = *localtime(&current_time);

	
	if(current_time == ((time_t)-1))
	{
		printf("failed to obtain the current time.\n");
		return 0;
	} 
	init_create_file(stime);
	serial_phy5_init();
	serial_hrm_init();

	while(1)
	{
		switch( central_state_get() ){
			case wait_for_data:
				if (serial_hrm_read()){
					//serial_new_data();
					save_data_val();
					central_state_set(hrm_data_received);
				}
				else if (serial_phy5_read()){
					//serial_new_data();
					save_data_val();
					central_state_set(phy5_data_received);
				}
				break;
				
				
			case hrm_data_received:
				if (serial_hrm_read()){
					if (data_len  == data_len_hrm){
						save_data_end();
						data_len	= 0;
						central_state_set(wait_for_data);
					}
					else {
						save_data_val();
						data_len += 1;
					}
					
				}				
				break;
				
			case phy5_data_received:
				if (serial_phy5_read()){
					if (data_len == data_len_phy5){
						save_data_end();
						data_len	= 0;
						central_state_set(wait_for_data);
					}
					else {
						save_data_val();
						data_len += 1;
					}
					
				}
				break;
			
			default:
				central_state_set( wait_for_data);
				break;
			}
	}
	
	printf("Closing socket and serial port\n");
	serial_hrm_close();
	serial_phy5_close();

	return 0;
}
