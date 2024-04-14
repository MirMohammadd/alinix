/**
 * @author Ali Mirmohammad
 * @file serialport.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

#include <alinix/types.h>
#include <alinix/enums.h>
#include <alinix/port.h>
#include <alinix/serialport.h>

enum COMPort PortAddress = COM1;
bool Initialized = false;

Init(enum COMPort port)
{
    PortAddress = port;

    outportb(PortAddress + 1, 0x00);    // Disable all interrupts
    outportb(PortAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PortAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PortAddress + 1, 0x00);    //                  (hi byte)
    outportb(PortAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PortAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PortAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    Initialized = true;
}

void SerialportWriteStr(char* str){
    for(int i = 0; str[i] != '\0'; ++i){
        SerialportWrite(str[i]);
    }
}

int SerialportSerialSendReady()
{
    return inportb(PortAddress + 5) & 0x20;
}

char SerialportRead()
{
    while (SerialReceiveReady() == 0);

    return inportb(PortAddress);
}

char SerialportRead()
{
    while (SerialReceiveReady() == 0);

    return inportb(PortAddress);
}

void SerialportInit(enum COMPort port)
{
    PortAddress = port;

    outportb(PortAddress + 1, 0x00);    // Disable all interrupts
    outportb(PortAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PortAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PortAddress + 1, 0x00);    //                  (hi byte)
    outportb(PortAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PortAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PortAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    Initialized = true;
}

int SerialportSerialReceiveReady()
{
    return inportb(PortAddress + 5) & 1;
}
