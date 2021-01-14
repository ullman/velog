/*
Copyright (C) 2018  Henrik Ullman
Copyright (C) 2020  Philip Freeman <elektron@halo.nu>
License: GPL Version 3
*/
#ifndef SERIAL_H
#define SERIAL_H
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
#include "vedirect.h"



extern volatile int run_loop;

int open_serial (char *sport);

int get_block (FILE * term_f, ve_direct_block_t **block);

void send_string (char *sstring, FILE * outfile);

void log_rotate (FILE * log_f, char *oarg, int log_n);

#endif /* SERIAL_H */
