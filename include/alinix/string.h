#ifndef __ALINIX_KERNEL_STRING_H
#define __ALINIX_KERNEL_STRING_H

#include <alinix/types.h>

#define _U 0x01 // Upper case letter mask
#define _L 0x02 // Lower case letter mask

#define isalpha(c)  (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
int strlen(const char* str);
bool strcmp(const char* strA, const char* strB);
bool strncmp(const char* s1, const char* s2, int n);
int IndexOf(const char* str, char c, uint32_t skip);
// bool Contains(const char* str, char c);

char* Uppercase(char* str);
char* Lowercase(char* str);
char* strcpy(char *s1, const char *s2);
char* strncpy(char *s1, const char *s2, unsigned int n);

#endif /*__ALINIX_KERNEL_STRING_H*/