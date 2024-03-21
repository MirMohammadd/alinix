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
 * @file io.h

 */
#ifndef ASM_H
#define ASM_H

#include <mm/mm.h>
#include <mm/paging.h>
#include <types.h>

extern uint8_t inportb(uint16_t port);
extern uint16_t inportw(uint16_t port);
extern void outportb(uint16_t port, uint8_t val);
extern void halt();
void enable_int();
void disable_int();

#endif