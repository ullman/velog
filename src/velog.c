/*
Copyright (C) 2018  Henrik Ullman
License: GPL Version 3
*/
#include "serial.h"
#define VERSION_MAJOR 0
#define VERSION_MINOR 1

volatile int run_loop = 1;

void print_manual ()
{
  printf ("velog - a serial log application for VE.Direct devices\n");
  printf ("Usage: velog -i device [-o file] [-r days]\n");
  printf (" -i\tSerial device\n");
  printf (" -o\tLogfile name\n");
  printf (" -r\tLog rotate interval in days\n");
  printf (" -v\tPrint version\n");
}

void print_version ()
{
  printf ("velog version %i.%i\n", VERSION_MAJOR, VERSION_MINOR);
  printf ("Copyright (C) 2018  Henrik Ullman\n");
  printf ("License: GPL Version 3\n");
  printf
    ("This is free software: you are free to change and redistribute it.\n");
  printf ("There is NO WARRANTY, to the extent permitted by law.\n");
}

void catch_exit ()
{
  run_loop = 0;
}

void free_line (char *line, int *def_i)
{
  if (*def_i)
    {
      free (line);
      *def_i = 0;
    }
}

int main (int argc, char *argv[])
{

  char *oarg;
  char *device;
  int c;
  int term_fd;
  FILE *term_f;
  FILE *log_f;
  time_t log_time;
  char *log_time_str;
  struct tm *log_time_tm;
  char *log_line;
  time_t start_time;
  int log_rotate_interval;
  int log_n;
  struct log_pack *packet;
  int serial_state;


  oarg = NULL;
  log_f = NULL;
  device = NULL;
  log_line = malloc (sizeof (char) * 100);
  log_time_str = malloc (sizeof (char) * 20);
  log_rotate_interval = 0;
  log_n = 0;


  while ((c = getopt (argc, argv, "i:o:r:hv")) != -1)
    {
      switch (c)
        {
        case 'i':
          device = optarg;
          printf ("Reading input from serial device: %s\n", device);
          break;
        case 'o':
          oarg = optarg;
          printf ("Saving output to file: %s\n", oarg);
          break;
        case 'r':
          log_rotate_interval = atoi (optarg);
          printf ("Rotating logfiles every %i days\n", log_rotate_interval);
          log_rotate_interval *= 86400; //measure in seconds
          break;
        case 'h':
          print_manual ();
          exit (0);
        case 'v':
          print_version ();
          exit (0);
        case '?':
          if (optopt == 'o')
            {
              fprintf (stderr, "Please specify logfile with [-o logfile]\n");
            }
          else if (optopt == 'i')
            {
              fprintf (stderr,
                       "Please specify serial device with -i device]\n");
            }
          else
            {
              fprintf (stderr, "Unknown option -%c\n", optopt);

            }
          return 1;
        default:
          abort ();
        }
    }

  if (!device)
    {
      printf ("%s: No device selected, please see %s -h\n", argv[0], argv[0]);
      exit (0);
    }
  if (oarg)
    {
      log_f = fopen (oarg, "w");
    }
  else
    {
      printf ("No logfile specified, printing to standard output\n");
    }
  printf ("press Ctrl-C to quit\n");
  signal (SIGINT, catch_exit);

  start_time = time (NULL);

  packet = malloc (sizeof (struct log_pack));
  packet->ppv_def = 0;
  packet->i_def = 0;
  packet->il_def = 0;
  packet->v_def = 0;

  term_fd = open_serial (device);
  if (term_fd == 1)
    {
      if (log_f)
        {
          fclose (log_f);
        }
      free (log_time_str);
      free (log_line);
      free (packet);


      exit (1);
    }
  term_f = fdopen (term_fd, "r");
  send_string ("PPV,I,IL,V,TIME\n", log_f);
  while (!NULL)
    {
      if (!(serial_state = parse_packet (term_f, packet)))
        {
          log_time = time (NULL);
          /*rotate log */
          if (oarg && log_rotate_interval != 0)
            {
              if ((log_time - start_time) / log_rotate_interval == 1)
                {
                  start_time += log_rotate_interval;
                  log_rotate (log_f, oarg, log_n);
                  log_n++;
                }
            }
          log_time_tm = localtime (&log_time);
          strftime (log_time_str, 20, "%Y-%m-%dT%H:%M:%S", log_time_tm);
          sprintf (log_line, "%s,%s,%s,%s,%s\n",
                   packet->PPV, packet->I, packet->IL, packet->V,
                   log_time_str);
          send_string (log_line, log_f);

        }


      free_line (packet->PPV, &packet->ppv_def);
      free_line (packet->I, &packet->i_def);
      free_line (packet->IL, &packet->il_def);
      free_line (packet->V, &packet->v_def);


      if (serial_state == 2)
        {
          sleep (10);
          term_fd = open_serial (device);
          if (term_fd == 1)
            {
              break;
            }
          term_f = fdopen (term_fd, "r");
        }

      if (run_loop == 0)
        {
          break;
        }


    }
  if (term_f)
    {
      fclose (term_f);          //may not close in case of interrupted stream
    }
  printf ("exiting...\n");
  if (log_f)
    {
      fclose (log_f);
    }
  free (log_time_str);
  free (log_line);
  free (packet);
  return 0;
}
