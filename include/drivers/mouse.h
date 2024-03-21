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
 * @file mouse.h

 */


#ifndef MOUSE_H
#define MOUSE_H

#include <types.h>


#define MOUSE_PORT 0x60
#define MOUSE_STATUS  0x80
#define MOUSE_ABIT 0x02
#define MOUSE_BBIT 0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08


/*Mouse clocks defined here*/


#define LEFT_CLICK      0x1
#define RIGHT_CLICK     0x2
#define MIDDLE_CLICK    0x4




#endif // MOUSE_H