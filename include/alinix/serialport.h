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
 * @file serialport.h

 */
#ifndef _ALINIX_KERNEL_SERIAL_PORT_H__
#define _ALINIX_KERNEL_SERIAL_PORT_H__

int SerialSendReady();

char Write(char a);

char WriteStr(char * str);


#endif 