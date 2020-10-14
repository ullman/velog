/*
Copyright (C) 2018  Henrik Ullman
Copyright (C) 2020  Philip J Freeman <elektron@halo.nu>
License: GPL Version 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "vedirect.h"
#include "serial.h"
#include "log_csv.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_PATCH 0

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
  printf ("velog version %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
  printf ("Copyright (C) 2018  Henrik Ullman\n");
  printf ("Copyright (C) 2020  Philip J Freeman <elektron@halo.nu>\n");
  printf ("License: GPL Version 3\n");
  printf
    ("This is free software: you are free to change and redistribute it.\n");
  printf ("There is NO WARRANTY, to the extent permitted by law.\n");
}

void catch_exit ()
{
  run_loop = 0;
}

int main (int argc, char *argv[])
{

  char *oarg;
  char *device;
  int c;
  int term_fd;
  FILE *term_f;
  time_t log_time;
  char *log_time_str;
  struct tm *log_time_tm;
  char *log_line;
  int log_rotate_interval;
  int serial_state;
  int i, j;
  ve_direct_block_t *block;
  ve_log_output_csv_t *out_csv = NULL;
  char *header=NULL;


  oarg = NULL;
  device = NULL;
  log_line = malloc (sizeof (char) * 100);
  log_time_str = malloc (sizeof (char) * 20);
  log_rotate_interval = 0;


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

  printf ("press Ctrl-C to quit\n");
  signal (SIGINT, catch_exit);

  term_fd = open_serial (device);
  if (term_fd == 1)
    {
      exit (1);
    }
  term_f = fdopen (term_fd, "r");
  while (!NULL)
    {
      if (!(serial_state = get_block (term_f, &block)))
        {
          if (block->device_info == NULL)
            {
              // fprintf(stderr, "Warning: skipping block w/o device_info :-/\n");
              ve_direct_free_block(block);
              continue;
            }

          int num_fields=0;
          char *field_list_mppt[] = { "PPV", "I", "IL", "V", "VPV" };
          char *field_list_inverter[] = { "V", "AC_OUT_V", "AC_OUT_I" };
          char *field_list_bmv[] = { "P","I", "V", "T", "CE", "SOC", "TTG" };
          char *field_list_unknown[] = { "I", "V" };
          char **fields_p = NULL;

          switch (block->device_info->type)
            {
                case ve_direct_device_type_mppt:
                  num_fields = 5;
                  fields_p = field_list_mppt;
                  break;

                case ve_direct_device_type_inverter:
                  num_fields = 3;
                  fields_p = field_list_inverter;
                  break;

                case ve_direct_device_type_bmv:
                  num_fields = 7;
                  fields_p = field_list_bmv;
                  break;

                case ve_direct_device_type_smart_charger:
                case ve_direct_device_type_unknown:
                  num_fields = 2;
                  fields_p = field_list_unknown;
                  break;
                default:
                  break;
            }

          if (oarg && header == NULL)
            {
              header = malloc(256);
              header[0]='\0';
              for ( i = 0; i < num_fields; i++)
                {
                  sprintf(&header[strlen(header)], "%s,", fields_p[i]);
                }
              sprintf (&header[strlen(header)], "TIME\n");
              out_csv = init_output_log_csv(oarg, header, log_rotate_interval);

            }

          log_time = time (NULL);

          log_time_tm = localtime (&log_time);
          strftime (log_time_str, 20, "%Y-%m-%dT%H:%M:%S", log_time_tm);

          log_line[0]='\0';
          for ( i = 0; i < num_fields; i++) {
            if (ve_direct_get_field_int(&j, block, fields_p[i]) == 0)
              sprintf(&log_line[strlen(log_line)], "%i,", j);
            else
              sprintf(&log_line[strlen(log_line)], ",");
          }

          sprintf (&log_line[strlen(log_line)], "%s\n", log_time_str);
          log_csv_send (out_csv, log_line);
          ve_direct_free_block(block);
        }


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
  if (out_csv) free(out_csv);
  free (log_time_str);
  free (log_line);
  return 0;
}
