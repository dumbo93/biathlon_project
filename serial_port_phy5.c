// https://github.com/xanthium-enterprises/Serial-Port-Programming-on-Linux/blob/master/USB2SERIAL_Read/Reciever%20(PC%20Side)/SerialPort_read.c
// https://www.cmrr.umn.edu/~strupp/serial.html
// http://www.i-programmer.info/programming/cc/10027-serial-c-and-the-raspberry-pi.html?start=4
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "serial_port_phy5.h"
#include "central_state.h"
#include "sensor_id.h"


struct termios serial_settings;
int fd_phy5 = 0;
char received_val[8];


int serial_phy5_init( void )
{
	printf("Hello from serial_init\n");
	
	if(!isatty(fd_phy5))
	{
		printf("error: is not TTY\n");
	}
	
	if(tcgetattr(fd_phy5, &serial_settings) < 0)
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
	fd_phy5 = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	// ttyUSB0: FT232 based USB2SERIAL converter
	// 0_RDWR:  Read/Write access to serial port
	// 0_NOCTTY: No terminal will control the process
	// O_NDELAY: Use non-blocking I/O
	
	// error checking
	if(fd_phy5 < 0)
	{
		printf("\n ERROR! in opening ttyACM0\n");
	}
	//printf("opend port\n");
	
	// apply configuration
	if(tcsetattr(fd_phy5, TCSAFLUSH, &serial_settings) < 0)
	{
		printf("error: set attr\n");
	}
	printf("serial_init done\n");
	return fd_phy5;
}


void serial_phy5_close( void )
{
	printf("closing serial port\n");
	close(fd_phy5);
}


int serial_phy5_read( void )
{
	if (read(fd_phy5, &current_value,1) > 0)
	{
		ascii_to_hex();
		ascii_to_int();
		//printf("Read value %s\n", current_value_hex);
		return 1;
	} 
	return 0;
}

void serial_new_data( void )
{
	switch ((int)current_value_hex){
		case HRM_SENSOR:
			printf("HRM %s\n", current_value_hex);
			central_state_set(hrm_data_received);
			break;
		
		case PHY5_SENSOR:
			printf("PHY5 %s\n", current_value_hex);
			central_state_set(phy5_data_received);
			break;
			
		default:
			printf("error %s\n", current_value_hex);
			central_state_set(wait_for_data);
			break;
	}
}

