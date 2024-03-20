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

	
#endif // _IO_PORTS_H_ 
