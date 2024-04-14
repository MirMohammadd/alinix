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
 * @file bootconsole.h

 */
#ifndef __ALINIX_KERNEL_BOOT_CONSOLE_H
#define __ALINIX_KERNEL_BOOT_CONSOLE_H

#include <alinix/types.h>

static int XOffset;
static int YOffset;
static bool writeToSerial;

static void Scroll();

uint8_t ForegroundColor;
uint8_t BackgroundColor;

void Init(bool enableSerial) ;

void Write(char c) ;

void Write(char* str) ;

void WriteLine(char* str);

void WriteLine() ;

void Clear();

void SetX(int x);

void SetY(int y);

uint16_t* GetBuffer();



/////////////////////////////////////////////////////
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15
};

#endif /*__ALINIX_KERNEL_BOOT_CONSOLE_H*/