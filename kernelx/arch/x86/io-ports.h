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

#ifndef _IO_PORTS_H_
#define _IO_PORTS_H_


/**	
 * @file io_ports.h
 * @author Konstantin Tcholokachvili
 * @@date 2007
 * @license MIT License
 * 
 * x86 I/O space access functions.
 */


/** 
	Write a value to an I/O port 
	@param value
	@param port
	@return None
*/
#define outb(port, value)		\
  __asm__ __volatile__ (		\
        "outb %b0,%w1"			\
        ::"a" (value),"Nd" (port)	\
        )				\
 
/** 
	Read one byte from I/O port
	@param port
	@return value
*/
#define inb(port)		\
({				\
  unsigned char _value;		\
  __asm__ __volatile__ (	\
        "inb %w1,%0"		\
        :"=a" (_value)		\
        :"Nd" (port)		\
        );			\
  _value;			\
})


/**
  * The following macro for reading and writing in the port output
  @param port
  @return value
*/
#define outw(port,val) \
    asm volatile ("out %w1, %w0" : : "a"(val), "Nd"(port))

/**
 * The following macro is used to read a double word (4 bytes) from an I/O port.
 @param port
 @return value
*/

#define inl(port,val) \
    asm volatile("in %d0, %w1" : "=a"(val) : "Nd"(port))

/**
 * An instruction to outputs 32 bit value from a register to specified port.
 * @param port
 * @return value
*/
#define outl(port,val) \
    asm volatile("in %d0, %w1" : "=a"(val) : "Nd"(port))

/**
 * reads a word (16 bits) from the specified port and stores the result in a variable
 * @param port
 * @return value
*/
#define inw(port, val) \
    asm volatile("in %w0, %w1" : "=a"(val) : "Nd"(port))

#define inwA(port) ({ \
    unsigned short _v; \
    __asm__ __volatile__ ("inw %w1, %0" : "=a" (_v) : "Nd" (port)); \
    _v; \
})

#endif // _IO_PORTS_H_ 
