
#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <sys/types.h>

char *strncpy(char *dest, const char *source, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
int stricmp(const char *s1, const char *s2);
int strnicmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int ch);
char *strrchr(const char *s, int ch);
char *strstr(const char *s1, const char *s2);
size_t strspn(const char *string, const char *control);
size_t strcspn(const char *string, const char *control);
char *strpbrk(const char *string, const char *control);

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);

int strcoll(const char *s1, const char *s2);

char *strdup(const char *s);

char *strlwr(char *s);
char *strupr(char *s);

char *strncat(char *s1, const char *s2, size_t n);
char *strnset(char *s, int c, size_t n);
char *strset(char *s, int c);
char *strrev(char *s);
char *strtok(char *string, const char *control);
char *strtok_r(char *string, const char *control, char **lasts);

char *strerror(int errnum);
char *strsignal(int signum);

void *memmove(void *dst, const void *src, size_t n);
void *memchr(const void *buf, int ch, size_t n);

void *memccpy(void *dst, const void *src, int c, size_t n);
int memicmp(const void *buf1, const void *buf2, size_t n);

// Intrinsic functions

void *memcpy(void *, const void *, size_t);
int memcmp(const void *, const void *, size_t);
void *memset(void *, int, size_t);

char *strcpy(char *, const char *);
char *strcat(char *, const char *);
int strcmp(const char *, const char *);
size_t strlen(const char *);

// Written by shainer

char *strtok (char *, const char *);
int _kstrncmp (const char *, const char *, int);

#endif