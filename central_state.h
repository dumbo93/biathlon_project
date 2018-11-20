#ifndef CENTRAL_STATE_H_
#define CENTRAL_STATE_H_

#include <stdint.h>

typedef enum{wait_for_data, new_data_received, hrm_data_received, phy5_data_received} state_t;

char current_value;

char current_value_hex[3];

uint8_t current_value_int;

void central_state_set(state_t next_state);

state_t central_state_get( void );

void ascii_to_hex( void );

void ascii_to_int( void ); 

#endif // CENTRAL_STATE_H_
