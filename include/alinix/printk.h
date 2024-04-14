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
 * @file printk.h

 */
#ifndef _ALINIX_KERNEL_PRINT_K_HEADER_H
#define _ALINIX_KERNEL_PRINT_K_HEADER_H

#include <alinix/types.h>
#include <alinix/system.h>
#include <alinix/serialport.h>

void Print(const char* data, uint32_t length) {
    /* Send data through serial port */
    if(screenMode == TextMode)
    {
        for (uint32_t i = 0; i < length; i++)
            Write(data[i]);
    }
    else if(Initialized && (gdbEnabled == false))
    {
        for (uint32_t i = 0; i < length; i++)
            Write(data[i]);
    }
}

#endif