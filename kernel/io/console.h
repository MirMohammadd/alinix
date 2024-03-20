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
