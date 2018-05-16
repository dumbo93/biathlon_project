/*
#include <stdio.h>
#include <strint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

// https://github.com/xanthium-enterprises/Serial-Port-Programming-on-Linux/blob/master/USB2SERIAL_Read/Reciever%20(PC%20Side)/SerialPort_read.c
// https://www.cmrr.umn.edu/~strupp/serial.html
// http://www.i-programmer.info/programming/cc/10027-serial-c-and-the-raspberry-pi.html?start=4



#define 	DONGLE_PORT "/dev/ttyACM0"
#define		BAUDRATE	1234 // random number choosen


int open_port( void )
{
	int fd;

	fd = open(DONGLE_PORT, 0_RDWR | 0_NOCTTY | 0_NDELAY);
	if (fd == -1)
	{
		perror("open_port: Unable to open /dev/ttyACM0 -");
	}
	else
		fcntl(fd, F_SETFL, 0);
	return (fd);
}


void close_port( fd )
{
	close(fd);
}


int read_port( fd )
{
	int recived_data;

	recived_data = fcntl(fd, F_SETFL, 0);

	return recived_data;
}

*/