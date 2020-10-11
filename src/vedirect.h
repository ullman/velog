/*
Copyright (C) 2020  "Philip J Freeman" <elektron@halo.nu>
License: GPL Version 3
*/
#ifndef VEDIRECT_H
#define VEDIRECT_H

typedef struct ve_direct_raw_fields_t {
	char				*name;
	char				*value;
	struct ve_direct_raw_fields_t	*next;
} ve_direct_raw_fields_t;

typedef struct ve_direct_block_t {
	unsigned int			pid;
	struct ve_direct_raw_fields_t	*raw_fields;
} ve_direct_block_t;

ve_direct_block_t	*ve_direct_parse_block(char *block_text_in);
void			ve_direct_free_block(ve_direct_block_t *block);

#endif /* VEDIRECT_H */
