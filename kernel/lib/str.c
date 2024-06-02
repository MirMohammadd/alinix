/**
 * @author Ali Mirmohammad
 * @file str.c
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
 * 	- Kernel string library implemented.
*/
#include <alinix/string.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("String library")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")


/**
 * Concatenate two strings.
 *
 * @param dst Pointer to the destination string where the concatenated string will be stored.
 * @param src Pointer to the source string to be appended to the destination string.
 * @return Pointer to the destination string after concatenation.
 *
 * @note This function concatenates the source string to the end of the destination string.
 *       It first finds the end of the destination string by iterating over it until it reaches the null character.
 *       Then, it appends the source string to the end of the destination string by copying each character from the source string until it reaches the null character.
 *       Finally, it returns a pointer to the destination string after concatenation.
 *
 * @example
 * // Concatenate two strings
 * char dst[100] = "Hello, ";
 * const char *src = "world!";
 * char *result = strcat(dst, src);
 * // The result string will be "Hello, world!"
 *
 * @see strcpy()
 * @see strncpy()
 */
char *strcat(char *dst, const char *src)
{
  char *cp = dst;
  while (*cp) cp++;
  while ((*cp++ = *src++) != '\0');
  return dst;
}