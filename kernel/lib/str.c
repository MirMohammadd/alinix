#include <alinix/string.h>


char *strcat(char *dst, const char *src)
{
  char *cp = dst;
  while (*cp) cp++;
  while ((*cp++ = *src++) != '\0');
  return dst;
}