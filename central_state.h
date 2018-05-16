#ifndef CENTRAL_STATE_H_
#define CENTRAL_STATE_H_

typedef enum{read_serial, got_value} state_t;

char current_value;

void central_state_set(state_t next_state);

state_t central_state_get( void );


#endif 
