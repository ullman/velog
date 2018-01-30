#include "serial.h"

void print_manual ()
{
  printf ("usage:\n");
  printf ("velog -i SERIAL_DEVICE [-o logfile]\n");
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
  char *log_line;


  oarg = NULL;
  log_f = NULL;
  device = NULL;
  log_line = malloc (sizeof (char) * 100);

  while ((c = getopt (argc, argv, "i:o:")) != -1)
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
      print_manual ();
      return 0;
    }
  if (oarg)
    {
      log_f = fopen (oarg, "w");
    }
  else
    {
      printf ("No logfile specified, printing to standard output\n");
    }
  struct log_pack *packet = malloc (sizeof (struct log_pack));
  term_fd = open_serial (device);
  term_f = fdopen (term_fd, "r");
  send_string ("PPV,\tI,\tIL,\tV,\tTIME\n", log_f);
  while (!NULL)
    {
      parse_packet (term_f, packet);
      log_time = time (NULL);
      sprintf (log_line, "%s,\t%s,\t%s,\t%s,\t%lld\n",
               packet->PPV, packet->I, packet->IL, packet->V,
               (long long) log_time);
      send_string (log_line, log_f);
    }
  return 0;
}
