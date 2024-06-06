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

/**
 * @abstraction:
 *  - Provides the RTC util, including update and sharing.
*/
#include <alinix/rtc.h>
#include <alinix/port.h>
#include <alinix/system/component.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("RTC module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

/**
 * @brief Checks if an update is in progress on the RTC.
 *
 * This function checks if an update is in progress on the Real-Time Clock (RTC).
 * It reads the status register at address 0x0A on the RTC's I/O port and checks if the 7th bit (0x80) is set.
 * If the bit is set, it returns true indicating that an update is in progress. Otherwise, it returns false.
 *
 * @return True if an update is in progress, false otherwise.
 */
bool UpdateInProgress(){
    outportb(0x70, 0x0A);
    return (inportb(0x71) & 0x80);
}

/**
 * @brief Reads a value from the specified register on the RTC.
 *
 * This function reads a value from the specified register on the Real-Time Clock (RTC).
 * It writes the register address to the RTC's I/O port and then reads the value from the data port.
 *
 * @param reg The register address to read from.
 * @return The value read from the specified register.
 */
uint8_t ReadRegister(int reg){
    outportb(0x70, reg);
    return inportb(0x71);
}

/**
 * @brief Gets the current second from the RTC.
 *
 * This function gets the current second from the Real-Time Clock (RTC).
 * It waits until an update is not in progress on the RTC and then reads the value from the second register.
 * If the 2nd bit of the register B is not set, it converts the value to BCD format.
 *
 * @return The current second from the RTC.
 */
uint32_t GetSecond(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x00);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

/**
 * @brief Gets the current minute from the RTC.
 *
 * This function gets the current minute from the Real-Time Clock (RTC).
 * It waits until an update is not in progress on the RTC and then reads the value from the minute register.
 * If the 2nd bit of the register B is not set, it converts the value to BCD format.
 *
 * @return The current minute from the RTC.
 */
uint32_t GetMinute(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x02);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

/**
 * @brief Gets the current hour from the RTC.
 *
 * This function gets the current hour from the Real-Time Clock (RTC).
 * It waits until an update is not in progress on the RTC and then reads the value from the hour register.
 * If the 2nd bit of the register B is not set, it converts the value to BCD format.
 * If the 1st bit of the register B is not set and the 7th bit of the hour value is set, it converts the value to 24-hour format.
 *
 * @return The current hour from the RTC.
 */
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

/**
 * @brief Gets the current day from the RTC.
 *
 * This function gets the current day from the Real-Time Clock (RTC).
 * It waits until an update is not in progress on the RTC and then reads the value from the day register.
 * If the 2nd bit of the register B is not set, it converts the value to BCD format.
 *
 * @return The current day from the RTC.
 */
uint32_t GetDay(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x07);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

/**
 * @brief Gets the current month from the RTC.
 *
 * This function gets the current month from the Real-Time Clock (RTC).
 * It waits until an update is not in progress on the RTC and then reads the value from the month register.
 * If the 2nd bit of the register B is not set, it converts the value to BCD format.
 *
 * @return The current month from the RTC.
 */
uint32_t GetMonth(){
    while(UpdateInProgress());
    uint32_t value = ReadRegister(0x08);
    uint32_t registerB = ReadRegister(0x0B);

    if(!(registerB & 0x04))
        value = (value & 0x0F) + ((value / 16) * 10);
    return value;
}

/**
 * @brief Gets the current year from the RTC.
 *
 * This function gets the current year from the Real-Time Clock (RTC).
 * It waits until an update is not in progress on the RTC and then reads the value from the year register.
 * If the 2nd bit of the register B is not set, it converts the value to BCD format.
 * It then calculates the full (4-digit) year by adding the current century and the year value.
 * If the calculated year is less than the current year, it adds 100 to the year value.
 *
 * @return The current year from the RTC.
 */
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