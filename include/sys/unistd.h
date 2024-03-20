#ifndef __UNISTD_H
#define __UNISTD_H

#include <types.h>
#include <stddef.h>

#define _SC_OPEN_MAX 4

ssize_t read(int , void *, size_t);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int close(int);



#endif