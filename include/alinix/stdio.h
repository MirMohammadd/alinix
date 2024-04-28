#ifndef __ALINIX_KERNEL_STDIO_H
#define __ALINIX_KERNEL_STDIO_H



int fprintf(FILE * file, const char *format, ...);

typedef struct {
    char *dummy[1];
}FILE;

#endif /*__ALINIX_KERNEL_STDIO_H*/