#ifndef CENTRAL_STATE_H_
#define CENTRAL_STATE_H_

typedef enum{read_serial, got_value} state_t;

char current_value;

char current_value_hex[3];

void central_state_set(state_t next_state);

state_t central_state_get( void );

void get_hex_val( void );

#endif 
