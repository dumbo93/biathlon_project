
// file for saving data values
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "sensor_id.h"

char save_data_name[32] = "logfile_";
FILE *fp;

void init_make_file(struct tm stime){
	stime.tm_mon = stime.tm_mon + 1;
	stime.tm_year = stime.tm_year- 100;
	
	file_name_set(stime.tm_mday);
	file_name_set(stime.tm_mon);
	file_name_set(stime.tm_year);
	
	strcat(save_data_name, "_");
	
	file_name_set(stime.tm_hour);
	file_name_set(stime.tm_min);
	
	printf("save_data_name %s\n", save_data_name);
	
	fp = fopen(save_data_name, "w");

	fprintf(fp, "sensor_name");
	fprintf(fp, "--");
	fprintf(fp, "sensor_time");
	fprintf(fp, "\n\n");

	fclose(fp);
}

void file_name_set(int name_char)
{
	char add_int[4];
	sprintf(add_int, "%d", name_char);
	strcat(save_data_name, add_int);
}


//called when data is resived
void save_data_val( char rec_val )
{
	fp = fopen(save_data_name, "a");

	fprintf(fp, "test");
	fprintf(fp, "--");
	fprintf(fp, "%c", rec_val);
	fprintf(fp, "\n");

	fclose(fp);
}



