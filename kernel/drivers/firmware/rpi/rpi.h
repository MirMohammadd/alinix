/**
 * @author Ali Mirmohammad
 * @file rpi.h
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
 *  - Header file.
 * 	- Provides util over the raspberry PI.
*/
#ifndef __ALINIX_RPI_H
#define __ALINIX_RPI_H

void uart_init(int raspi);
void uart_putc(unsigned char c);
unsigned char uart_getc();
void uart_puts(const char* str);


#endif /*__ALINIX_RPI_H*/