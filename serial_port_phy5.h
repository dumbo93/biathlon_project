#ifndef SERIAL_PORT_PHY5_H_
#define SERIAL_PORT_PHY5_H_

int serial_phy5_init( void );


//int serial_open( );

void serial_phy5_close( void );

int serial_phy5_read( void );

void serial_new_data( void );


#endif // SERIAL_PORT_H_
