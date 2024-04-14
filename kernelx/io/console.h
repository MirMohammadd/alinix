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

#pragma once

/**
 * @file console.h
 * @author Konstantin Tcholokachvili
 * @date 2014, 2016
 * @license MIT License
 *
 * Console's constants and functions
 */

#include <lib/types.h>

#define CONSOLE_MODE_CANON 1
#define CONSOLE_MODE_ECHO  2

struct console;

ret_t console_setup(struct console **terminal_out,
		void (*write_function)(uchar_t c));

ret_t console_read(struct console *t, uchar_t *dst_buffer, size_t len);

void console_write(struct console *t, void *src_buffer, uint16_t len);

void console_add_character(struct console *cons, char c);

void console_set_mode(struct console *cons, uint8_t mode);
