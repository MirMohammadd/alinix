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
 * @file enums.h

 */
#ifndef __ALINIX_KERNEL_ENUMS_HEADER_H
#define __ALINIX_KERNEL_ENUMS_HEADER_H

typedef enum priority{
    /*A class that defined a proccess priority*/
    LOWEST = -150,
    LOWER = -50,
    LOW = -10,
    NORMAL = 0,
    HIGH = 10,
    HIGHER = 50,
    HIGHEST = 150
}priority_t;

enum ScreenMode
{
    TextMode,
    GraphicsMode
};

enum PowerRequest
{
    None,
    Shutdown,
    Reboot
};

enum EndpointDirection 
{
    Out,
    In
};

enum EndpointType 
{
    Control,
    Isochronous,
    Bulk,
    Interrupt
};

enum COMPort {
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2E8
};

#endif /*__ALINIX_KERNEL_ENUMS_HEADER_H*/