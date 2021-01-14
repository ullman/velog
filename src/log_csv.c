/*
Copyright (C) 2018  Henrik Ullman
Copyright (C) 2020  Philip J Freeman <elektron@halo.nu>
License: GPL Version 3
*/
#
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log_csv.h"

ve_log_output_csv_t *init_output_log_csv(char *filepath, char *header, int log_rotate_interval)
{
	ve_log_output_csv_t *obj;

	obj = calloc(1, sizeof(ve_log_output_csv_t));
	obj->filepath = filepath;

	if (strcmp(obj->filepath, "-") == 0) {
		obj->file = stdout;
	} else {
		obj->file = fopen (obj->filepath, "w");
	}

	obj->header_needed = 1;
	obj->header = header;

	obj->start_time = time(NULL);

	obj->start_time_tm = localtime (&obj->start_time);
	obj->start_time_tm->tm_hour = 0;
	obj->start_time_tm->tm_min = 0;
	obj->start_time_tm->tm_sec = 0;

	obj->start_time = mktime(obj->start_time_tm);

	obj->log_rotate_interval = log_rotate_interval;
	obj->log_n = 0;

	return obj;
}

void free_output_log_csv(ve_log_output_csv_t *obj)
{
	fclose(obj->file);
	free(obj);
}

void log_csv_send (ve_log_output_csv_t *obj, char *sstring)
{

	time_t log_time;
	int log_change;

	log_time = time (NULL);

	/* check for rotate log */
	if (obj->log_rotate_interval != 0 && strcmp(obj->filepath, "-") != 0) {

		log_change = (log_time - obj->start_time) / obj->log_rotate_interval;

		if (log_change != 0) {
			// why not name every logfile with the date instead? this is weird...
			char new_name[100];
			sprintf(new_name, "%s.%i", obj->filepath, obj->log_n);
			fclose(obj->file);
			rename(obj->filepath, new_name);
			obj->file = fopen (obj->filepath, "w");
			obj->start_time += obj->log_rotate_interval * log_change;
			obj->header_needed = 1;
			obj->log_n++;
		}
	}

	// print header
	if (obj->header_needed) {
		obj->header_needed = 0;
		fprintf(obj->file, "%s", obj->header);
	}
	fprintf (obj->file, "%s", sstring);
	fflush (obj->file);
}
