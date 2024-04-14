/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file port.h

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