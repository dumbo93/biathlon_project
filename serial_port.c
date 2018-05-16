// https://github.com/xanthium-enterprises/Serial-Port-Programming-on-Linux/blob/master/USB2SERIAL_Read/Reciever%20(PC%20Side)/SerialPort_read.c
// https://www.cmrr.umn.edu/~strupp/serial.html
// http://www.i-programmer.info/programming/cc/10027-serial-c-and-the-raspberry-pi.html?start=4
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "serial_port.h"
#include "central_state.h"



struct termios serial_settings;
int fd = 0;
char received_val[8];

int serial_init( void )
{
	printf("Hello from serial_init\n");
	
	if(!isatty(fd))
	{
		printf("error: is not TTY\n");
	}
	
	if(tcgetattr(fd, &serial_settings) < 0)
	{
		printf("error: current config\n");
	}
	
	// turn off input processing
	serial_settings.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
	
	// turn of output processing
	serial_settings.c_oflag = 0;
	
	// no line processing
	serial_settings.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	
	
	// turn off character processing
	serial_settings.c_cflag &= ~(CSIZE | PARENB);
	serial_settings.c_cflag |= CS8;
	
	// one input argument is enough to return read()
	serial_settings.c_cc[VMIN] = 10;
	serial_settings.c_cc[VTIME] = 0;
	
	// communication speed, baud rate
	if(cfsetispeed(&serial_settings, B115200) <0 || cfsetospeed(&serial_settings, B115200) < 0)
	{
		printf("error: baud rate\n");
	}
	
	// open port
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	// ttyUSB0: FT232 based USB2SERIAL converter
	// 0_RDWR:  Read/Write access to serial port
	// 0_NOCTTY: No terminal will control the process
	// O_NDELAY: Use non-blocking I/O
	
	// error checking
	if(fd < 0)
	{
		printf("\n ERROR! in opening ttyACM0\n");
	}
	//printf("opend port\n");
	
	// apply configuration
	if(tcsetattr(fd, TCSAFLUSH, &serial_settings) < 0)
	{
		printf("error: set attr\n");
	}
	printf("serial_init done\n");
	return fd;
}

/*
int serial_open( int fd )
{
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	// ttyUSB0: FT232 based USB2SERIAL converter
	// 0_RDWR:  Read/Write access to serial port
	// 0_NOCTTY: No terminal will control the process
	
	// error checking
	if(fd < 0)
		printf("\n ERROR! in opening ttyACM0\n");
// 	/else
// 	{
// 		//printf("\n ttyACM0 Opened successfully\n");
// 		printf("opend port open");
// 	}
	return fd;
}
*/

void serial_close( void )
{
	printf("closing serial port\n");
	close(fd);
}


void serial_read( void )
{
	if (read(fd, &current_value,1) > 0)
	{
		printf("Read value %s\n", &current_value);
		central_state_set( got_value );
	}
	//return *received_val;
}

/*
void serial_write( void )
{
	//write(fd, buffer, len);
}
*/
