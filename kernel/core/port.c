/**
 * @author Ali Mirmohammad
 * @file port.c
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
/**
 * @abstraction:
 *  - Provides util for the kernel I/O ports.
*/
#include <alinix/port.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Port I/O")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")



/**
 * @brief Reads an 8-bit value from the specified I/O port.
 *
 * @param _port The I/O port address to read from.
 * @return The 8-bit value read from the port.
 *
 * @details
 * This function uses inline assembly to read an 8-bit value from the specified
 * I/O port. The `inb` instruction is used to read a byte from the port, and the
 * value is stored in the `rv` variable. The `rv` variable is then returned.
 *
 * @note
 * The `_port` parameter should be a valid I/O port address.
 */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
/**
 * @brief Writes an 8-bit value to the specified I/O port.
 *
 * @param _port The I/O port address to write to.
 * @param _data The 8-bit value to write to the port.
 *
 * @details
 * This function uses inline assembly to write an 8-bit value to the specified
 * I/O port. The `outb` instruction is used to write a byte to the port, and the
 * value is passed in the `_data` parameter. The `_port` parameter specifies
 * the I/O port address to write to.
 *
 * @note
 * The `_port` parameter should be a valid I/O port address.
 */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/**
 * @brief Reads a 16-bit value from the specified I/O port.
 *
 * @param _port The I/O port address to read from.
 * @return The 16-bit value read from the port.
 *
 * @details
 * This function uses inline assembly to read a 16-bit value from the specified
 * I/O port. The `inw` instruction is used to read a word from the port, and the
 * value is stored in the `rv` variable. The `rv` variable is then returned.
 *
 * @note
 * The `_port` parameter should be a valid I/O port address.
 */
unsigned short inportw(unsigned short _port)
{
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/**
 * @brief Writes a 16-bit value to the specified I/O port.
 *
 * @param _port The I/O port address to write to.
 * @param _data The 16-bit value to write to the port.
 *
 * @details
 * This function uses inline assembly to write a 16-bit value to the specified
 * I/O port. The `outw` instruction is used to write a word to the port, and the
 * value is passed in the `_data` parameter. The `_port` parameter specifies
 * the I/O port address to write to.
 *
 * @note
 * The `_port` parameter should be a valid I/O port address.
 */
void outportw(unsigned short _port, unsigned short _data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (_port), "a" (_data));
}

/**
 * @brief Reads a 32-bit value from the specified I/O port.
 *
 * @param _port The I/O port address to read from.
 * @return The 32-bit value read from the port.
 *
 * @details
 * This function uses inline assembly to read a 32-bit value from the specified
 * I/O port. The `inl` instruction is used to read a doubleword from the port,
 * and the value is stored in the `val` variable. The `val` variable is then
 * returned.
 *
 * @note
 * The `_port` parameter should be a valid I/O port address.
 */
unsigned int inportl(unsigned short _port)
{
    unsigned int val;
    __asm__ __volatile__ ("inl %%dx, %%eax" : "=a" (val) : "d" (_port));
    return( val );
}

/**
 * @brief Writes a 32-bit value to the specified I/O port.
 *
 * @param _port The I/O port address to write to.
 * @param _data The 32-bit value to write to the port.
 *
 * @details
 * This function uses inline assembly to write a 32-bit value to the specified
 * I/O port. The `outl` instruction is used to write a doubleword to the port,
 * and the value is passed in the `_data` parameter. The `_port` parameter
 * specifies the I/O port address to write to.
 *
 * @note
 * The `_port` parameter should be a valid I/O port address.
 */
void outportl(unsigned short _port, unsigned int _data)
{
    __asm__ __volatile__ ("outl %%eax, %%dx" : : "d" (_port), "a" (_data));
}

/**
 * @brief Reads a block of data from the specified I/O port.
 *
 * @param port The I/O port address to read from.
 * @param data A pointer to the buffer to store the read data.
 * @param size The number of bytes to read.
 *
 * @details
 * This function uses inline assembly to read a block of data from the specified
 * I/O port. The `rep insw` instruction is used to read a block of words from the
 * port, and the data is stored in the buffer pointed to by the `data` parameter.
 * The number of bytes to read is specified by the `size` parameter.
 *
 * @note
 * The `port` parameter should be a valid I/O port address.
 * The `data` parameter should point to a valid buffer that is at least `size` bytes
 * long.
 */
void inportsm(unsigned short port, unsigned char * data, unsigned long size)
{
    asm volatile ("rep insw" : "+D" (data), "+c" (size) : "d" (port) : "memory");
}

/**
 * @brief Writes a block of data to the specified I/O port.
 *
 * @param port The I/O port address to write to.
 * @param data A pointer to the buffer containing the data to write.
 * @param size The number of bytes to write.
 *
 * @details
 * This function uses inline assembly to write a block of data to the specified
 * I/O port. The `rep outsw` instruction is used to write a block of words to the
 * port, and the data is read from the buffer pointed to by the `data` parameter.
 * The number of bytes to write is specified by the `size` parameter.
 *
 * @note
 * The `port` parameter should be a valid I/O port address.
 * The `data` parameter should point to a valid buffer that is at least `size` bytes
 * long.
 */
void outportsm(unsigned short port, unsigned char * data, unsigned long size) {
    asm volatile ("rep outsw" : "+S" (data), "+c" (size) : "d" (port));
}

/**
 * @brief Writes a 32-bit value to the specified memory address.
 *
 * @param addr The memory address to write to.
 * @param val The 32-bit value to write.
 *
 * @details
 * This function writes a 32-bit value to the specified memory address. The value
 * is written using a pointer to a volatile `uint32_t` variable, which ensures that
 * the write is not optimized away by the compiler. The memory address is specified
 * by the `addr` parameter, and the value to write is specified by the `val` parameter.
 *
 * @note
 * The `addr` parameter should be a valid memory address.
 */
void writeMemReg(const uint32_t addr, const uint32_t val) {
    *(volatile uint32_t*)addr = val;
}

/**
 * @brief Reads a 32-bit value from the specified memory address.
 *
 * @param addr The memory address to read from.
 * @return The 32-bit value read from the memory address.
 *
 * @details
 * This function reads a 32-bit value from the specified memory address. The value
 * is read using a pointer to a volatile `uint32_t` variable, which ensures that
 * the read is not optimized away by the compiler. The memory address is specified
 * by the `addr` parameter, and the value read is returned by the function.
 *
 * @note
 * The `addr` parameter should be a valid memory address.
 */
uint32_t readMemReg(const uint32_t addr) {
    return *(volatile uint32_t*)addr;
}