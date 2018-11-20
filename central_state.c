
#include "central_state.h"

state_t current_state = wait_for_data;

void central_state_set(state_t next_state)
{
	current_state = next_state;
}


state_t central_state_get( void )
{
	return current_state;
}


void ascii_to_hex( void )
{
	unsigned n;
	
	n = current_value/ 0x10;
	
	if (n < 10){
		current_value_hex[0] = n +'0';
		
	}else {
		current_value_hex[0] = (n -10) + 'A';
	}
	
	n = current_value % 0x10;
	
	if (n < 10){
		current_value_hex[1] = n +'0';
		
	}else {
		current_value_hex[1] = (n -10) + 'A';
	}
	
	current_value_hex[2] = '\0';
}


void ascii_to_int( void )
{
	if (current_value >= '0' && current_value <= '9')
	{
		current_value_int = current_value - '0';
	}
}
