#include <alinix/port.h>


inline unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

inline void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

inline unsigned short inportw(unsigned short _port)
{
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

inline void outportw(unsigned short _port, unsigned short _data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (_port), "a" (_data));
}
inline unsigned int inportl(unsigned short _port)
{
    unsigned int val;
    __asm__ __volatile__ ("inl %%dx, %%eax" : "=a" (val) : "d" (_port));
    return( val );
}
inline void outportl(unsigned short _port, unsigned int _data)
{
    __asm__ __volatile__ ("outl %%eax, %%dx" : : "d" (_port), "a" (_data));
}

inline void inportsm(unsigned short port, unsigned char * data, unsigned long size)
{
    asm volatile ("rep insw" : "+D" (data), "+c" (size) : "d" (port) : "memory");
}

inline void outportsm(unsigned short port, unsigned char * data, unsigned long size) {
    asm volatile ("rep outsw" : "+S" (data), "+c" (size) : "d" (port));
}

inline void writeMemReg(const uint32_t addr, const uint32_t val) {
    *(volatile uint32_t*)addr = val;
}

inline uint32_t readMemReg(const uint32_t addr) {
    return *(volatile uint32_t*)addr;
}