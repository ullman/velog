/*
Copyright (C) 2018  Henrik Ullman
License: GPL Version 3
*/

#include "serial.h"

int open_serial (char *sport)
{
  struct termios uio;
  int term_fd;


  memset (&uio, 0, sizeof (uio));

  cfsetispeed (&uio, B19200);
  cfsetospeed (&uio, B19200);

  uio.c_iflag = 0;
  uio.c_oflag = 0;
  uio.c_lflag = 0;
  uio.c_cflag = CS8 | CREAD | CLOCAL;

  uio.c_cc[VMIN] = 0;
  uio.c_cc[VTIME] = 5;

  uio.c_iflag &= ~(IXON | IXOFF | IXANY);
  term_fd = open (sport, O_RDONLY);
  if (term_fd == -1)
    {
      perror ("Error opening serial port");
      exit (1);
    }
  tcsetattr (term_fd, TCSANOW, &uio);
  tcflush (term_fd, TCIOFLUSH);

  return term_fd;
}

void parse_line (char *needle, char *log_line, char **store_loc)
{
  char *cut_loc;
  if (log_line == strstr (log_line, needle))
    {
      cut_loc = strstr (log_line, "\t");
      *store_loc = malloc (sizeof (char) * strlen (cut_loc + 1));
      strcpy (*store_loc, cut_loc + 1);
    }
}

void parse_packet (FILE * term_f, struct log_pack *packet)
{
//TODO can be improved a lot for stability & cleanness
  char *log_line;
  log_line = malloc (sizeof (char) * 100);

//find start of packet
  while (!strstr (log_line, "Checksum"))
    {
      fgets (log_line, 100, term_f);
    }
  memset (log_line, 0, strlen (log_line));
//start reading packet
  while (!strstr (log_line, "Checksum"))
    {
      fgets (log_line, 100, term_f);
      log_line[strcspn (log_line, "\r\n")] = '\0';
      parse_line ("PPV\t", log_line, &packet->PPV);
      parse_line ("I\t", log_line, &packet->I);
      parse_line ("IL\t", log_line, &packet->IL);
      parse_line ("V\t", log_line, &packet->V);
    }

}

void send_string (char *sstring, FILE * outfile)
{
  if (outfile)
    {
      fprintf (outfile, "%s", sstring);
      fflush (outfile);
    }
  else
    {
      printf ("%s", sstring);
    }
}

void log_rotate (FILE * log_f, char *oarg, int log_n)
{
  char new_name[100];
  sprintf (new_name, "%s.%i", oarg, log_n);
  fclose (log_f);
  rename (oarg, new_name);
  log_f = fopen (oarg, "w");
  send_string ("PPV,\tI,\tIL,\tV,\tTIME\n", log_f);

}
