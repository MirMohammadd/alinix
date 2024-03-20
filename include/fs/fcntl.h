#ifndef _FCNTL_H
#define _FCNTL_H

#include <sys/types.h>

#define O_RDONLY	0x00
#define O_WRONLY    0x01
#define O_RDWR      0x02

#define O_CREAT		0x40
#define O_APPEND	0x400


int  creat(const char *, mode_t);
int  fcntl(int, int, ...);
int  open(const char *, int, ...);

#endif