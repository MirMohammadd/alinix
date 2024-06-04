/**
 * @author Ali Mirmohammad
 * @file smbios.c
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
 *  - Provides util for BIOS.
*/
#include <alinix/smbios.h>
#include <alinix/types.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("SMBIOS")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


/**
 * Create a copy of a null-terminated string.
 *
 * This function creates a copy of a null-terminated string by dynamically allocating memory for the new string and copying the characters from the source string.
 * It performs the following steps:
 *
 * 1. Calculates the length of the source string using the `strlen` function.
 * 2. Dynamically allocates memory for the new string, including space for the null terminating character.
 * 3. Copies the characters from the source string to the new string.
 * 4. Sets the null terminating character at the end of the new string.
 * 5. Returns the new string.
 *
 * @param src The source string to be copied.
 *
 * @return A pointer to the newly allocated copy of the string.
 *
 * @throws None.
 */
char* CopyString(char* src){
    int len = strlen(src);
    char* ret = (char*)malloc(sizeof(char)*(len+1));
    ret[len] = '\0';
    return ret;
}