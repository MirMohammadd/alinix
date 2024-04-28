#ifndef __ALINIX_KERNEL_STDIO_H
#define __ALINIX_KERNEL_STDIO_H




typedef struct {
    char *dummy[1];
}FILE;
int fprintf(FILE * file, const char *format, ...);

#endif /*__ALINIX_KERNEL_STDIO_H*/