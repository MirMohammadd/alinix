#ifndef __ALINIX_KERNEL_STRING_H
#define __ALINIX_KERNEL_STRING_H

#include <alinix/types.h>

static int strlen(const char* str);
static bool strcmp(const char* strA, const char* strB);
static bool strncmp(const char* s1, const char* s2, int n);
static int IndexOf(const char* str, char c, uint32_t skip);
static bool Contains(const char* str, char c);

            static char* Uppercase(char* str);
            static char* Lowercase(char* str);
            static char Uppercase(char c);
            static char Lowercase(char c);
            static char* strcpy(char *s1, const char *s2);
            static char* strncpy(char *s1, const char *s2, unsigned int n);

#endif /*__ALINIX_KERNEL_STRING_H*/