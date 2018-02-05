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

int parse_packet (FILE * term_f, struct log_pack *packet)
{
  //TODO add custom parameters to log
  char *log_line;
  int checksum;
  int i;
  int fd;
  fd_set set;
  int to;
  struct timeval timeout;


  checksum = 0;

  log_line = malloc (sizeof (char) * 100);

  memset (log_line, 0, strlen (log_line));

  /*Timeout */
  fd = fileno (term_f);
  FD_ZERO (&set);
  FD_SET (fd, &set);
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  while (!strstr (log_line, "Checksum"))
    {
      to = select (fd + 1, &set, NULL, NULL, &timeout);
      if (to == 0)
        {
          printf ("Read timeout, please check serial input...\n");
          return 1;
        }
      else
        {
          fgets (log_line, 100, term_f);

          for (i = 0; i < strlen (log_line); i++)
            {
              checksum = checksum + (int) log_line[i];
            }

          log_line[strcspn (log_line, "\r\n")] = '\0';
          parse_line ("PPV\t", log_line, &packet->PPV);
          parse_line ("I\t", log_line, &packet->I);
          parse_line ("IL\t", log_line, &packet->IL);
          parse_line ("V\t", log_line, &packet->V);
        }
    }

  free (log_line);

  if (checksum % 256 != 0)
    {
      fprintf (stderr, "Checksum error for packet, discarding...\n");
      return 1;
    }
  else
    {
      return 0;
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
