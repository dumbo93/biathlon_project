
#include "central_state.h"

state_t state = read_serial;

void central_state_set(state_t next_state)
{
	state = next_state;
}


state_t central_state_get( void )
{
	return state;
}
