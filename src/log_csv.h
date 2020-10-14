/*
Copyright (C) 2018  Henrik Ullman
Copyright (C) 2020  Philip Freeman <elektron@halo.nu>
License: GPL Version 3
*/
#ifndef LOG_CSV_H
#define LOG_CSV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

typedef struct ve_log_output_csv_t {
	char		*filepath;
	FILE		*file;
	int		header_needed;
	char		*header;
	int		log_rotate_interval;
	int		log_n;
	time_t		start_time;
	struct tm	*start_time_tm;

} ve_log_output_csv_t;

ve_log_output_csv_t	*init_output_log_csv(char *filepath, char *header, int log_rotate_interval);
void			free_output_log_csv(ve_log_output_csv_t *obj);
void			log_csv_send(ve_log_output_csv_t *obj, char *sstring);

#endif /* LOG_CSV_H */
