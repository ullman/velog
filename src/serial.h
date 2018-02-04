/*
Copyright (C) 2018  Henrik Ullman
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


struct log_pack
{
  char *PPV;
  char *V;
  char *I;
  char *IL;
};

int open_serial (char *sport);

void parse_line (char *needle, char *log_line, char **store_loc);

void parse_packet (FILE * term_f, struct log_pack *packet);

void send_string (char *sstring, FILE * outfile);

void log_rotate (FILE *log_f,char *oarg, int log_n);

#endif /* SERIAL_H */
