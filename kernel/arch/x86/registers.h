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
#ifndef _REGISTERS_H_
#define _REGISTERS_H_

/**
 * @struct regs
 * 
 * This defines what the stack looks like after an ISR was running
 */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int interrupt_number, error_code;
    unsigned int eip, cs, eflags, user_esp, ss;    
};

#endif // _REGISTERS_H_
