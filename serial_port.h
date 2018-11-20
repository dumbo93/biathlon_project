#ifndef SERIAL_PORT_H_
#define SERIAL_PORT_H_

int serial_init( void );

//int serial_open( );

void serial_close( void );

int serial_read( void );

void serial_new_data( void );

//void serial_write( void );

#endif // SERIAL_PORT_H_
