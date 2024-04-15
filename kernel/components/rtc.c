/**
 * @author Ali Mirmohammad
 * @file rtc.c
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

#include <alinix/rtc.h>
#include <alinix/port.h>
#include <alinix/system/component.h>

bool UpdateInProgress(){
    outportb(0x70, 0x0A);
    return (inportb(0x71) & 0x80);
}

uint8_t ReadRegister(int reg){
    outportb(0x70, reg);
    return inportb(0x71);
}


uint32_t GetSecond(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x00);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}


uint32_t GetMinute(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x02);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

uint32_t GetHour(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x04);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = ((value & 0x0F) + (((value & 0x70) / 16) * 10) ) | (value & 0x80);
    
    if(!(registerB & 0x02) && (value & 0x80))
        value = ((value & 0x7F) + 12) % 24;

    return value;
}

uint32_t GetDay(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x07);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

uint32_t GetMonth(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x08);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

uint32_t GetYear(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x09);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    
    // Calculate the full (4-digit) year
    value += (CURRENT_YEAR / 100) * 100;
    if(value < CURRENT_YEAR)
        value += 100;

    return value;
}