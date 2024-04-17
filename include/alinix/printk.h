/**
 * @author Ali Mirmohammad
 * @file rtc.h
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

#ifndef _ALINIX_KERNEL_PRINT_K_HEADER_H
#define _ALINIX_KERNEL_PRINT_K_HEADER_H

#include <alinix/types.h>
#include <alinix/system.h>
#include <alinix/serialport.h>
#include <alinix/enums.h>
bool gdbEnabled = false;
bool Initialized = false;


enum ScreenMode_t screenMode = TextMode;


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