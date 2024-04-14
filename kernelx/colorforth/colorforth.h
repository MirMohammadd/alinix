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
/*
 * Copyright (c) 2016, 2017, 2020 Konstantin Tcholokachvili
 * All rights reserved.
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <io/console.h>

#define FORTH_DICTIONARY 0
#define MACRO_DICTIONARY 1

typedef int32_t cell_t;

typedef struct colorforth_word
{
	cell_t                 name;
	void                  *code_address;
} word_t;

struct editor_args
{
	struct console *cons;
	uint32_t initrd_start;
	uint32_t initrd_end;
};

void editor(void *args);
cell_t pack(const char *word_name);
char *unpack(cell_t word);
void run_block(const cell_t nb_block);
void dot_s(void);
void dispatch_word(cell_t word);
word_t lookup_word(cell_t name, const bool_t force_dictionary);
void colorforth_initialize(void);
void erase_stack(void);
