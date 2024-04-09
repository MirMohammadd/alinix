#ifndef _STRING_H_COOMMON_HEISEN_KERNEL_DEFINED_G
#define _STRING_H_COOMMON_HEISEN_KERNEL_DEFINED_G

#include <types.h>
#ifdef __cplusplus
#include <list.h>
#endif

#ifndef size_t_defined
// typedef unsigned int size_t; // Define size_t if it's not already defined
#endif

#if !defined(_SIZE_T) && !defined(_SIZE_T_DEFINED)
#  define _SIZE_T_DEFINED
#if defined(_WIN64)
   typedef unsigned __int64 size_t;
#else
   typedef unsigned int size_t;
#endif
#  if defined(__cplusplus)
#    define _SIZE_T std::size_t
#  else
#    define _SIZE_T size_t
#  endif
#endif

#include "stddef.h"
#ifdef __cplusplus
extern "C" {
#endif



extern void* memset (void * p, int val, size_t len);
extern void* memcpy (void* to, const void* from, size_t len);
void* memmove(void* dstptr, const void* srcptr, size_t size);
size_t strlen(const char* str);


#ifdef __cplusplus
int str_IndexOf(const char* str, char c, int skip = 0);
#else 
int str_IndexOf(const char* str, char c, int skip);
#endif


bool str_Contains(const char* str, char c);
// List<char*> str_Split(const char* str, char d);
char* str_Uppercase(char* str);
char* str_Lowercase(char* str);
char* str_Add(char* str, char c);
char* str_Combine(char* part1, char* part2);
int strcmp(const char *s1, const char *s2);
int memcmp(const void* aptr, const void* bptr, size_t size);
#ifdef __cplusplus
List<char*> str_Split(const char* str, char d);
#endif

bool isvalid(unsigned char key);


#ifdef __cplusplus
}
#endif
#endif