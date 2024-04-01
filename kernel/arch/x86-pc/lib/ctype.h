#ifndef __CTYPE_H
#define __CTYPE_H

#define OFFSET 32 /* Distance from a uppercase character to the correspondent lowercase in ASCII */

int isdigit(int c);
int isalpha(int c);
int isalnum(int c);
int isxdigit(int c);
int islower(int c);
int isupper(int c);
int tolower(int c);
int toupper(int c);
int isspace(int c);
int iscntrl(int c);
int ispunct(int c);

#endif