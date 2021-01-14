/*
Copyright (C) 2020  "Philip J Freeman" <elektron@halo.nu>
License: GPL Version 3
*/
#ifndef VEDIRECT_H
#define VEDIRECT_H

typedef enum {
	ve_direct_device_type_unknown = 0,
	ve_direct_device_type_bmv,
	ve_direct_device_type_mppt,
	ve_direct_device_type_inverter,
	ve_direct_device_type_smart_charger
} ve_direct_device_type;

typedef enum {
	ve_direct_value_type_bool = 1,
	ve_direct_value_type_hex,
	ve_direct_value_type_int,
	ve_direct_value_type_str
} ve_direct_value_type;

typedef struct ve_direct_fields_t {
	char				*name;
	ve_direct_value_type		type;
	void				*value;
	struct ve_direct_fields_t	*next;
} ve_direct_fields_t;

typedef struct ve_direct_device_info_t {
	char				*name;
	ve_direct_device_type		type;
} ve_direct_device_info_t;

typedef struct ve_direct_raw_fields_t {
	char				*name;
	char				*value;
	struct ve_direct_raw_fields_t	*next;
} ve_direct_raw_fields_t;

typedef struct ve_direct_block_t {
	unsigned int			pid;
	struct ve_direct_device_info_t	*device_info;
	struct ve_direct_fields_t	*fields;
	struct ve_direct_raw_fields_t	*raw_fields;
} ve_direct_block_t;

ve_direct_block_t	*ve_direct_parse_block(char *block_text_in);
void			*ve_direct_get_field_value(ve_direct_block_t *block, char *field_name);
int			ve_direct_get_field_int(int *int_p, ve_direct_block_t *block, char *field_name);
void			ve_direct_print_block(ve_direct_block_t *block);
void			ve_direct_free_block(ve_direct_block_t *block);

/* private functions */
ve_direct_device_info_t *_ve_direct_get_device_info(unsigned int pid);

#endif /* VEDIRECT_H */
