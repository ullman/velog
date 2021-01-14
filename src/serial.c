/*
Copyright (C) 2018  Henrik Ullman
Copyright (C) 2020  Philip J Freeman <elektron@halo.nu>
License: GPL Version 3
*/

#include "serial.h"

int open_serial (char *sport)
{
  struct termios uio;
  int term_fd;


  memset (&uio, 0, sizeof (uio));

  cfsetispeed (&uio, B19200);

  term_fd = open (sport, O_RDONLY);

  uio.c_lflag = ICANON;

  uio.c_oflag &= ~OPOST;
  uio.c_cflag &= ~PARENB;
  uio.c_cflag &= ~CSIZE;

  uio.c_cflag |= CS8 | CREAD | CLOCAL;

  uio.c_cc[VMIN] = 0;
  uio.c_cc[VTIME] = 5;

  uio.c_iflag &= ~(IXON | IXOFF | IXANY);
  if (term_fd == -1)
    {
      perror ("Error opening serial port");
      return 1;
    }
  tcsetattr (term_fd, TCSANOW, &uio);
  tcflush (term_fd, TCIOFLUSH);

  return term_fd;
}

int get_block (FILE * term_f, ve_direct_block_t **block_p)
{
  //TODO add custom parameters to log
  char block_buf[1025];
  int l=0;
  int fd;
  int a;
  fd_set set;
  int to;
  struct timeval timeout;
  size_t len;

  ve_direct_block_t *b;

  /*Timeout */

  fd = fileno (term_f);
  FD_ZERO (&set);
  FD_SET (fd, &set);
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  while ((a = getc (term_f)) != EOF)
    {
      to = select (FD_SETSIZE, &set, NULL, NULL, &timeout);

      len = 0;
      ioctl (fd, FIONREAD, &len);

      if (to == 0)
        {
          fprintf (stderr,
                   "Read timeout, please check serial input...\n");
          return 1;
        }

      if (run_loop == 0)
        {
          return 1;
        }

      if (len == 0)
        {
          fprintf (stderr,
                   "Device disconnected, retrying in 10 sec...\n");
          return 2;
        }

      if (l > 1024)
        {
          fprintf (stderr,
                   "Error: Exhausted block read buffer!\n");
          return 1;
        }

      block_buf[l]=a;

      /* skip hex protocol frames */
      if (block_buf[0] == ':' && block_buf[l] == '\n')
        {
          l = 0;
          continue;
        }

      if (l < 9)
        {
          l++;
          continue;
        }

      block_buf[l+1]='\0'; // add null terminator after last byte in buffer

      // test for end of block
      if (strstr(&block_buf[l-9], "Checksum") == &block_buf[l-9])
        {
          l = 0;
          b = ve_direct_parse_block(&block_buf[0]);
          if (b == NULL)
            return 1;
          *block_p = b;
          return 0;
        }

      l++;

    }

  fprintf (stderr,
           "Error: got EOF from serial stream!\n");

  return 1;

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
  send_string ("PPV,I,IL,V,VPV,TIME\n", log_f);

}
