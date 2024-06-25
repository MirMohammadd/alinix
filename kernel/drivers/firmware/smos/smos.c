/**
 * @author Ali Mirmohammad
 * @file smos.c
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
 *  - Provides util for SMOS.
*/
#include <alinix/smos.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("SMOS")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")



/**
 * @ref https://wiki.osdev.org/Unreal_Mode
*/

int century_register = 0x00;                                // Set by ACPI table parsing code if possible
unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned int year;

/**
 * Checks if an update is in progress by reading the update-in-progress flag from the RTC.
 *
 * @return 1 if an update is in progress, 0 otherwise.
 *
 * @throws None
 */

static inline int get_update_in_progress_flag(){
    outportb(cmos_address,0x0A);
    return inportb((cmos_data) & 0x80);
}

/**
 * Reads the value of a specified RTC register.
 *
 * @param reg The register address to read from.
 *
 * @return The value read from the specified RTC register.
 *
 * @throws None
 */
static inline unsigned char get_RTC_register(int reg) {
    outportb(cmos_address, reg);
    return inportb(cmos_data);
}

/**
 * Reads the real-time clock (RTC) and updates the global variables `second`, `minute`, `hour`, `day`, `month`, and `year` with the current time and date.
 *
 * This function first checks if an update is in progress by calling the `get_update_in_progress_flag()` function.
 * It then reads the values of the RTC registers using the `get_RTC_register()` function and assigns them to the respective variables (`second`, `minute`, `hour`, `day`, `month`, `year`, `century`).
 *
 * The function enters a loop and continues reading the RTC registers until the values of all the variables are the same as the previous iteration.
 * This ensures that the read values are stable.
 *
 * After the loop, the function reads the value of register B using the `get_RTC_register()` function and assigns it to the `registerB` variable.
 *
 * The function then performs some calculations to convert the binary BCD (Binary-coded decimal) values to decimal values.
 * If the least significant nibble of `second`, `minute`, `hour`, `day`, `month`, and `year` is greater than 9, it adds the corresponding value of the most significant nibble multiplied by 10.
 * This is done to convert the BCD values to decimal.
 *
 * If the second least significant bit of `registerB` is not set (0x02), it checks if the most significant bit of `hour` is set (0x80).
 * If it is set, it adds 12 to the `hour` value and takes the modulo 24 to handle the case when the hour value exceeds 23.
 *
 * Finally, the function calculates the full (4-digit) year based on the `century` value.
 * If the `century_register` is not 0, it multiplies the `century` value by 100 and adds it to the `year` value.
 * If the `century_register` is 0, it multiplies the current year (assumed to be `CURRENT_YEAR`) by 100 and adds it to the `year` value.
 * If the calculated year is less than the current year, it adds 100 to the `year` value.
 *
 * @throws None
 */
void read_rtc() {
    unsigned char century;
    unsigned char last_second;
    unsigned char last_minute;
    unsigned char last_hour;
    unsigned char last_day;
    unsigned char last_month;
    unsigned char last_year;
    unsigned char last_century;
    unsigned char registerB;

    while (get_update_in_progress_flag());                // Make sure an update isn't in progress
      second = get_RTC_register(0x00);
      minute = get_RTC_register(0x02);
      hour = get_RTC_register(0x04);
      day = get_RTC_register(0x07);
      month = get_RTC_register(0x08);
      year = get_RTC_register(0x09);
      if(century_register != 0) {
            century = get_RTC_register(century_register);
      }

    do{
        last_second = second;
        last_minute = minute;
        last_hour = hour;
        last_day = day;
        last_month = month;
        last_year = year;
        last_century = century;

        while (get_update_in_progress_flag());           // Make sure an update isn't in progress
        second = get_RTC_register(0x00);
        minute = get_RTC_register(0x02);
        hour = get_RTC_register(0x04);
        day = get_RTC_register(0x07);
        month = get_RTC_register(0x08);
        year = get_RTC_register(0x09);
        if(century_register != 0) {
                century = get_RTC_register(century_register);
        }
    }while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
               (last_day != day) || (last_month != month) || (last_year != year) ||
               (last_century != century) );
    
    registerB = get_RTC_register(0x0B);

    if (!(registerB & 0x04)){
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
        if(century_register != 0) {
                century = (century & 0x0F) + ((century / 16) * 10);
        }
    }
    if (!(registerB & 0x02) && (hour & 0x80)) {
            hour = ((hour & 0x7F) + 12) % 24;
      }
 
      // Calculate the full (4-digit) year
 
      if(century_register != 0) {
            year += century * 100;
      } else {
            year += (CURRENT_YEAR / 100) * 100;
            if(year < CURRENT_YEAR) year += 100;
      }
}