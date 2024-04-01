#ifndef __STDDEF__H
#define __STDDEF__H

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EOF
#define EOF (-1)
#endif

#define BUFSIZ 512

#define KERNEL_SIZE 0x200

#ifndef TRUE 
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0 
#endif

typedef unsigned int size_t;
typedef unsigned long long qword;
typedef unsigned short int ushort;
typedef unsigned char byte;

#endif