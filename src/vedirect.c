/*
Copyright (C) 2020  "Philip J Freeman" <elektron@halo.nu>
License: GPL Version 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vedirect.h"

void _ve_direct_free_fields_from_block(ve_direct_fields_t *head)
{
	if (head->next != NULL)
		_ve_direct_free_fields_from_block(head->next);

	free(head->name);
	free(head->value);
	free(head);
}

char *_ve_direct_get_raw_field_value_str_from_block(ve_direct_block_t *block, char *field_name)
{
	ve_direct_raw_fields_t  *fptr;

	fptr = block->raw_fields;
	while (fptr != NULL) {
		if (strcmp(fptr->name, field_name) == 0)
			return fptr->value;
		fptr = fptr->next;
	}
	return NULL;
}

void _ve_direct_free_raw_fields_from_block(ve_direct_raw_fields_t *head)
{
	if (head->next != NULL)
		_ve_direct_free_raw_fields_from_block(head->next);

	free(head->name);
	free(head->value);
	free(head);
}

int _ve_direct_parse_block_raw_fields(ve_direct_block_t *block, char *block_text_in)
{
	char                    *p = NULL;
	ve_direct_raw_fields_t  *fptr_new, *fptr=NULL;

	p = block_text_in;

	while ( (p = strstr(p, "\r\n")) != NULL) {

		// initialize a new raw field member
		fptr_new = calloc(1, sizeof(ve_direct_raw_fields_t));
		if (fptr_new == NULL) {
			fprintf(stderr, "Error allocating memory for raw field.\n");
			ve_direct_free_block(block);
			return 1;
		}

		if (block->raw_fields == NULL) {

			block->raw_fields = fptr_new;
			fptr = fptr_new;
		} else {

			fptr->next = fptr_new;
			fptr = fptr_new;
		}

		if (sscanf(p, "\r\n%ms\t%ms", &fptr->name, &fptr->value) != 2) {
			/* the last byte of a block is a checksum integer that is not neccesarily
			printable. if we're parsing the Checksum field this sscanf can partially
			fail. Handle that case before throwing out the block. */
			if (fptr->name != NULL && strcmp(fptr->name, "Checksum") == 0) {
				fptr->value = malloc(2);
				fptr->value[0] = p[11]; // The eleventh byte should be our checksum
				fptr->value[1] = '\0';
			} else {
				fprintf(stderr, "Error scanning field in from:%s\n\n", p);
				ve_direct_free_block(block);
				return 1;
			}
		};


		p = p+2; // advance pointer past the initial \r\n of this record...
	}
	return 0;
}

void ve_direct_free_block(ve_direct_block_t *block)
{
	if (block == NULL) return;

	if (block->device_info !=NULL) {
		free(block->device_info->name);
		free(block->device_info);
	}

	if (block->raw_fields != NULL)
		_ve_direct_free_raw_fields_from_block(block->raw_fields);

	if (block->fields != NULL)
		_ve_direct_free_fields_from_block(block->fields);

	free(block);
}

int _ve_direct_add_field(ve_direct_block_t *block, char * field_name, ve_direct_value_type value_type, char *units, char *description)
{
	int			i;
	char			*value_str;
	ve_direct_fields_t	*p, *p_tmp;

	value_str = _ve_direct_get_raw_field_value_str_from_block(block, field_name);
	if (value_str == NULL){
		return 1;
	}

	p = calloc(1, sizeof(ve_direct_fields_t));

	if (p == NULL) {
		fprintf(stderr, "Error allocating memory for field.\n");
		ve_direct_free_block(block);
		return 1;
	}

	p->name = malloc(strlen(field_name)+1);
	strcpy(p->name, field_name);

	p->type = value_type;

	switch (value_type) {

	case ve_direct_value_type_hex:
		sscanf(value_str, "%x", &i);
		p->value = malloc(sizeof(int));
		*(int *)p->value = i;
		break;

	case ve_direct_value_type_int:
		sscanf(value_str, "%i", &i);
		p->value = malloc(sizeof(int));
		*(int *)p->value = i;
		break;

	case ve_direct_value_type_bool:
		if (strcmp(value_str, "YES") == 0)
			i = 1;
		else
			i = 0;
		p->value = malloc(sizeof(int));
		*(int *)p->value = i;
		break;

	case ve_direct_value_type_str:
		p->value = malloc(strlen(value_str)+1);
		strcpy((char *)p->value, value_str);
		break;
	}

	if (block->fields == NULL) {
		block->fields = p;
	} else {
		p_tmp = block->fields;
		while (p_tmp->next != NULL) p_tmp = p_tmp->next;
		p_tmp->next = p;
	}
	return 0;
}

void *ve_direct_get_field_value(ve_direct_block_t *block, char *field_name)
{
	ve_direct_fields_t	*field_p;

	field_p = block->fields;
	while (field_p != NULL) {
		if (strcmp(field_p->name, field_name) == 0)
			return field_p->value;
		field_p = field_p->next;
	}
	return NULL;
}

int ve_direct_get_field_int(int *int_p, ve_direct_block_t *block, char *field_name)
{
	void *p;

	p = ve_direct_get_field_value(block, field_name);
	if (p == NULL) {
		return -1;
	}
	*int_p = *(int *)p;
	return 0;
}

void ve_direct_print_block(ve_direct_block_t *b)
{
	ve_direct_raw_fields_t  *raw_fields_p;
	ve_direct_fields_t  *fields_p;

	printf("block at memory address %p:\n", b);
	printf("\tpid:\t0x%0X\n", b->pid);
	printf("\tdevice_info:\n");
	if (b->device_info == NULL) {
		printf("\t\t(null)\n");
	} else {
		if (b->device_info->name != NULL)
			printf("\t\tname:\t%s\n", b->device_info->name);
		printf("\t\ttype:\t");
		if (b->device_info->name != NULL)
		switch (b->device_info->type) {

		case ve_direct_device_type_unknown:
			printf("unknown\n");
			break;
		case ve_direct_device_type_bmv:
			printf("Battery Monitor\n");
			break;
		case ve_direct_device_type_mppt:
			printf("MPPT Charge Controller\n");
			break;
		case ve_direct_device_type_inverter:
			printf("Inverter\n");
			break;
		case ve_direct_device_type_smart_charger:
			printf("Smart Charger\n");
			break;
		}
	}
	printf("\traw fields:\n");
	for (raw_fields_p=b->raw_fields; raw_fields_p!=NULL; raw_fields_p=raw_fields_p->next) {
		printf("\t\t%s:\t%s\n", raw_fields_p->name, raw_fields_p->value);
	}

	printf("\tparsed fields:\n");
	for (fields_p=b->fields; fields_p!=NULL; fields_p=fields_p->next) {
		printf("\t\t%s:\t", fields_p->name);
		switch (fields_p->type) {

		case ve_direct_value_type_bool:
			if (*(int *)fields_p->value)
				printf("True/On/Yes\n");
			else
				printf("False/Off/No\n");
			break;

		case ve_direct_value_type_hex:
			printf("0x%0X\n", *(int *)fields_p->value);
			break;

		case ve_direct_value_type_int:
			printf("%i\n", *(int *)fields_p->value);
			break;

		case ve_direct_value_type_str:
			printf("%s\n", (char *)fields_p->value);
			break;

		}
	}
	printf("\n");
}

ve_direct_block_t *ve_direct_parse_block(char *block_text_in)
{
	int			*pid_p, checksum = 0;
	ve_direct_block_t	*block;


	// validate block (sum of all bytes in the block % 256 should equal 0)

	for (int i=0; i<strlen(block_text_in); i++)
		checksum = (checksum + (int) block_text_in[i]) & 255;

	if (checksum != 0) {
		fprintf (stderr, "VE.Direct block parsing failed, bad checksum (0!=%i).\n", checksum%256);
		return NULL;
	}


	// allocate a block data structure

	block = calloc(1,sizeof(ve_direct_block_t));
	if (block == NULL) {
		fprintf (stderr, "Error allocating memory for block.\n");
		return NULL;
	}


	// split block into linked list of raw text fields and values

	if (_ve_direct_parse_block_raw_fields(block, block_text_in) != 0) {
		return NULL;
	}

	// Parse raw fields into their intended types

	_ve_direct_add_field(block, "PID", ve_direct_value_type_hex, "", "Product ID");

	pid_p = ve_direct_get_field_value(block, "PID");
	if (pid_p != NULL) {
		block->pid = *(int *) pid_p;
		block->device_info = _ve_direct_get_device_info(block->pid);
	}

	//General
	_ve_direct_add_field(block, "V", ve_direct_value_type_int, "mV", "Main or channel 1 battery voltage");
	_ve_direct_add_field(block, "I", ve_direct_value_type_int, "mA", "Main or channel 1 battery current");
	_ve_direct_add_field(block, "SER#", ve_direct_value_type_str, "", "Serial number of the device");

	//MPPT Charge Controller
	_ve_direct_add_field(block, "VPV", ve_direct_value_type_int, "mV", "Panel voltage");
	_ve_direct_add_field(block, "PPV", ve_direct_value_type_int, "W", "Panel power");
	_ve_direct_add_field(block, "IL", ve_direct_value_type_int, "mA", "Load current");

	//Inverter Stuff
	_ve_direct_add_field(block, "AC_OUT_V", ve_direct_value_type_int, "0.01V", "AC output voltage");
	_ve_direct_add_field(block, "AC_OUT_I", ve_direct_value_type_int, "0.1A", "AC output current");
	_ve_direct_add_field(block, "T", ve_direct_value_type_int, "C", "Battery temperature");
	_ve_direct_add_field(block, "P", ve_direct_value_type_int, "W", "Instantaaneous power");
	_ve_direct_add_field(block, "CE", ve_direct_value_type_int, "mAh", "Consumed amp hours");
	_ve_direct_add_field(block, "SOC", ve_direct_value_type_int, "%", "State-of-charge");
	_ve_direct_add_field(block, "TTG", ve_direct_value_type_int, "m", "Time-to-go");


	return block;
}
