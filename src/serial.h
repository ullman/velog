/*
Copyright (C) 2018  Henrik Ullman
Copyright (C) 2020  Philip Freeman <elektron@halo.nu>
License: GPL Version 3
*/
#ifndef SERIAL_H
#define SERIAL_H

int open_serial (char *sport);

int get_block (FILE * term_f, ve_direct_block_t **block);

#endif /* SERIAL_H */
