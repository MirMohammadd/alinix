

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

#define MAX_DIGITS_IN_INTEGER 11

#ifndef EOF
#define EOF (-1)
#endif

void putchar (char ch);
int atoi (const char *);
int printf (const char *, ...);
int puts (char *s);
int scanf (const char *, ...);
char *gets (char *);
int getchar (void);

int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);

#endif