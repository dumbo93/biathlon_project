/*
//sensor_info

struct sensor_info{
	char name[50];
	char file_name[20];
	uint8_t	sensor_type;
	uint8_t	com_type;
	int	value;
	uint32_t time;
};


char sensor_info_make_file_name( )
{
	//use the time in the file name
	// char of size 50
	name = "/home/sensordata/" + sensorname + "_" + time + ".txt";

}

void sensor_info_set_info(struct sensor_info sensor, char name, uint8_t type, uint8_t com_type, int value, uint32_t time){
	sensor_info.name 		= name;//
	sensor_info.file_name 	= sensor_info_make_file_name();
	sensor_info.sensor_type = sensor_type;
	sensor_info.com_type 	= com_type;
	sensor_info.value 		= value;
	sensor_info.time 		= time;
}
*/