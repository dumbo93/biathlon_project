
// file for saving data values
#include <stdio.h>
//#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "save_data.h"
#include "central_state.h"



char save_data_name[32] = "logfile_";
FILE *fp;

void init_create_file(struct tm stime){
	stime.tm_mon = stime.tm_mon + 1;
	stime.tm_year = stime.tm_year - 100;
	
	file_name_set(stime.tm_mday);
	file_name_set(stime.tm_mon);
	file_name_set(stime.tm_year);
	
	strcat(save_data_name, "_");
	
	file_name_set(stime.tm_hour);
	file_name_set(stime.tm_min);
	
	printf("save_data_name %s\n", save_data_name);
	
	fp = fopen(save_data_name, "w");

	fprintf(fp, "Logging starter at time: ");
	fprintf(fp, "%d:%d", stime.tm_hour, stime.tm_min);
	fprintf(fp, "\n\n");

	fclose(fp);
}

void file_name_set(int time_value)
{
	if (time_value < 10)
	{
		strcat(save_data_name, "0");
	}
	char add_int[4];
	sprintf(add_int, "%d", time_value);
	strcat(save_data_name, add_int);
}


//called when data is resived
void save_data_val( void)
{
	fp = fopen(save_data_name, "a");

	fprintf(fp, "%d", current_value_int);

	fclose(fp);
}

void save_data_end( void)
{
	fp = fopen(save_data_name, "a");

	fprintf(fp, "\n");

	fclose(fp);
}

