/*
Copyright (C) 2020  "Philip J Freeman" <elektron@halo.nu>
License: GPL Version 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vedirect.h"

char *_ve_direct_get_field_value_str_from_block(ve_direct_block_t *block, char *field_name)
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
			if (fptr->name != NULL && strstr(fptr->name, "Checksum") != NULL) {
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

	if (block->raw_fields != NULL)
		_ve_direct_free_raw_fields_from_block(block->raw_fields);
	free(block);
}

ve_direct_block_t *ve_direct_parse_block(char *block_text_in)
{
	int			checksum = 0;
	char			*p = NULL;
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


	// parse block into linked list of fields

	if (_ve_direct_parse_block_raw_fields(block, block_text_in) != 0) {
		return NULL;
	}

	// scan the PID field into an int
	p = _ve_direct_get_field_value_str_from_block(block, "PID");
	if (p != NULL) {
		sscanf(p, "%x", &block->pid);
	}

	return block;
}
