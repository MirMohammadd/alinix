/**
 * @author Ali Mirmohammad
 * @file print.c
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
 *  - Provides utility for printing info on the kernel screen.
 *  - Provides printing different data types.
*/
#include <alinix/print.h>
#include <alinix/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Print utility")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


/**
 * Print a hexadecimal representation of a given byte.
 *
 * This function prints a hexadecimal representation of a given byte to the console.
 * It performs the following steps:
 *
 * 1. Create a temporary character array `foo` with a length of 2.
 * 2. Create a character array `hex` representing the hexadecimal digits.
 * 3. Set the first character of `foo` to the corresponding hexadecimal digit of the most significant 4 bits of `key`.
 * 4. Set the second character of `foo` to the corresponding hexadecimal digit of the least significant 4 bits of `key`.
 * 5. Call the `Write` function to write `foo` to the console.
 *
 * @param key The byte to be printed in hexadecimal format.
 *
 * @return None.
 *
 * @throws None.
 */
void printfHex(uint8_t key){
    char *foo = "00";
    char *hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    Write(foo);
}

/**
 * Print a hexadecimal representation of a given 32-bit unsigned integer.
 *
 * This function prints a hexadecimal representation of a given 32-bit unsigned integer to the console.
 * It performs the following steps:
 *
 * 1. Extract the most significant byte of `key` and print it in hexadecimal format using the `printfHex` function.
 * 2. Extract the second most significant byte of `key` and print it in hexadecimal format using the `printfHex` function.
 * 3. Extract the third most significant byte of `key` and print it in hexadecimal format using the `printfHex` function.
 * 4. Extract the least significant byte of `key` and print it in hexadecimal format using the `printfHex` function.
 *
 * @param key The 32-bit unsigned integer to be printed in hexadecimal format.
 *
 * @return None.
 *
 * @throws None.
 */
void printfHex32(uint32_t key)
{
    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex(key & 0xFF);
}