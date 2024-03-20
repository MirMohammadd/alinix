#ifndef _IO_H
#define _IO_H

#define sti() __asm__ __volatile__ ("sti");
#define cli() __asm__ __volatile__ ("cli");
 
extern unsigned char inportb (int);
extern void outportb (int, int);
 
#endif