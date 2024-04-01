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
 * @file keyboard.h

 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/**
 * @file keyboard.h
 * @author Konstantin Tcholokachvili
 * @date 2007, 2013, 2014, 2016
 * @license MIT License
 *
 * Keyboard handling
 */

#include <arch/x86/registers.h>
#include <io/console.h>
#include <lib/types.h>

#define KEYBOARD_DATA_PORT      0x60
#define KEYBOARD_COMMAND_PORT   0x64

#define KBD_CR_NL       0x0a
#define KBD_BACKSPACE   0x08
#define KBD_TABULATION  0x09

// See scancodes at wiki.osdev.org/PS2/2_Keyboard
#define KEY_ESCAPE      0x01
#define KEY_BACKSPACE   0x0e
#define KEY_TAB         0x0f
#define KEY_ENTER       0x1c
#define KEY_LEFT_CTRL   0x1d
#define KEY_LEFT_SHIFT  0x2a
#define KEY_RIGHT_SHIFT 0x36
#define KEY_LEFT_ALT    0x38
#define KEY_SPACE       0x39
#define KEY_CAPS_LOCK   0x3a
#define KEY_F1          0x3b
#define KEY_F2          0x3c
#define KEY_F3          0x3d
#define KEY_F4          0x3e
#define KEY_F5          0x3f
#define KEY_F6          0x40
#define KEY_F7          0x41
#define KEY_F8          0x42
#define KEY_F9          0x43
#define KEY_F10         0x44
#define KEY_NUMBER_LOCK 0x45
#define KEY_SCROLL_LOCK 0x46
#define KEY_F11         0x57
#define KEY_F12         0x58
#define KEY_UP          0x48
#define KEY_DOWN        0x50
#define KEY_LEFT        0x4b
#define KEY_RIGHT       0x4d
#define KEY_PAGE_UP	0x49
#define KEY_PAGE_DOWN	0x51

#define CAPS_LOCK 0x3A


#define BACKSPACE 14
#define ESCAPE 1
#define PAGEUP 73
#define PAGEDOWN 81


/*Keyboard key scancode defined here (ascii)*/
#define Q_KEY 0x18
#define W_KEY 0x19
#define E_KEY 0x1A
#define R_KEY 0x1B
#define T_KEY 0x1C
#define Y_KEY 0x1D
#define U_KEY 0x1E
#define I_KEY 0x1F
#define O_KEY 0x20
#define P_KEY 0x21
#define A_KEY 0x26
#define S_KEY 0x27
#define D_KEY 0x20
#define F_KEY 0x29
#define G_KEY 0x2A
#define H_KEY 0x2B
#define J_KEY 0x2C
#define K_KEY 0X2D
#define L_KEY 0x2E
#define Z_KEY 0x35
#define X_KEY 0x36
#define C_KEY 0x37
#define V_KEY 0x38
#define B_KEY 0x39
#define N_KEY 0x3B
#define M_KEY 0x3C

/** Handles keyboard
 *
 * @param r Registers status during the interrupt
 */
void keyboard_interrupt_handler(int number);

void keyboard_setup(struct console *term);

char keyboard_get_keymap(uchar_t i);

char keyboard_special_caps_keys(char key);


#endif // _KEYBOARD_H_
