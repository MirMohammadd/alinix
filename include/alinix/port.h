/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __ALINIX_KERNEL_PORT_H
#define __ALINIX_KERNEL_PORT_H

#include <alinix/types.h>
#define insl(port, buffer, count) asm volatile("cld; rep; insl" :: "D" (buffer), "d" (port), "c" (count))

inline static unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

inline static void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

inline static unsigned short inportw(unsigned short _port)
{
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

inline static void outportw(unsigned short _port, unsigned short _data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (_port), "a" (_data));
}
inline static unsigned int inportl(unsigned short _port)
{
    unsigned int val;
    __asm__ __volatile__ ("inl %%dx, %%eax" : "=a" (val) : "d" (_port));
    return( val );
}
inline static void outportl(unsigned short _port, unsigned int _data)
{
    __asm__ __volatile__ ("outl %%eax, %%dx" : : "d" (_port), "a" (_data));
}

inline static void inportsm(unsigned short port, unsigned char * data, unsigned long size)
{
    asm volatile ("rep insw" : "+D" (data), "+c" (size) : "d" (port) : "memory");
}

inline static void outportsm(unsigned short port, unsigned char * data, unsigned long size) {
    asm volatile ("rep outsw" : "+S" (data), "+c" (size) : "d" (port));
}

inline static void writeMemReg(const uint32_t addr, const uint32_t val) {
    *(volatile uint32_t*)addr = val;
}

inline static uint32_t readMemReg(const uint32_t addr) {
    return *(volatile uint32_t*)addr;
}

#endif // __ALINIX_KERNEL_PORT_H