#ifndef __ALINIX_KERNEL_UUID_H
#define __ALINIX_KERNEL_UUID_H

#include <alinix/types.h>

#define UUID_SIZE 16
#define	UUID_STRING_LEN		36


typedef struct {
	uint8_t b[UUID_SIZE];
} uuid_t;

#endif