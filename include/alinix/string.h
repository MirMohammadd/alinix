#ifndef __ALINIX_KERNEL_STRING_H
#define __ALINIX_KERNEL_STRING_H

#include <alinix/types.h>

int strlen(const char* str);
bool strcmp(const char* strA, const char* strB);
bool strncmp(const char* s1, const char* s2, int n);
int IndexOf(const char* str, char c, uint32_t skip);
// bool Contains(const char* str, char c);

char* Uppercase(char* str);
char* Lowercase(char* str);
char Uppercase(char c);
char Lowercase(char c);
char* strcpy(char *s1, const char *s2);
char* strncpy(char *s1, const char *s2, unsigned int n);

#endif /*__ALINIX_KERNEL_STRING_H*/