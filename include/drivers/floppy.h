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
 * @file floppy.h

 */

#ifndef FLOPPY_H
#define FLOPPY_H

#include <types.h>

enum floppy_io{
    FLOPPY_DOR = 0x3F2,
    FLOPPY_MSR = 0x3F4,
    FLOPPY_FIFO    = 0x3F5,
    FLOPPY_CTRL    = 0x3F7
};



#endif