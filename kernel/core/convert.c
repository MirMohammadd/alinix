/**
 * @author Ali Mirmohammad
 * @file convert.c
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
 *  - Provides the converting data types to each other util.
*/
#include <alinix/convert.h>
#include <alinix/memory.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Converts data types to each other")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

/**
 * @brief Converts a string representation of an integer to an integer value.
 *
 * This function takes a string as input and converts it to an integer value. It supports both positive and negative integers.
 * The function assumes that the input string is a valid representation of an integer.
 *
 * @param string The string representation of the integer.
 * @return The integer value of the input string.
 *
 * @todo Add the missing return type to the function declaration. The return type should be an integer.
 */
StringToInt(char* string) // TODO Add the missing return type here.
{
    int result = 0;
    unsigned int digit;
    int sign;

    // while (IsSpace(*string)) {
    //     string += 1;
    // }

    /*
    * Check for a sign.
    */

    if (*string == '-') {
        sign = 1;
        string += 1;
    } else {
        sign = 0;
        if (*string == '+') {
            string += 1;
        }
    }

    for ( ; ; string += 1) {
        digit = *string - '0';
        if (digit > 9) {
            break;
        }
        result = (10*result) + digit;
    }

    if (sign) {
        return -result;
    }
    return result;
}
/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function checks if the given character is a whitespace character. It returns true if the character is a space, tab, newline, vertical tab, form feed, or carriage return, and false otherwise.
 *
 * @param c The character to check.
 * @return True if the character is a whitespace character, false otherwise.
 */
int IsSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

char* IntToHexString(uint8_t w)
{
    static const char* digits = "0123456789ABCDEF";
    uint32_t hexSize = sizeof(uint32_t)<<1;
    char* rc =  malloc(sizeof(char[hexSize + 1])); //Terminate string with 0
    memset(rc, 0, hexSize + 1);

    for (uint32_t i=0, j=(hexSize-1)*4 ; i<hexSize; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

/**
 * @brief Converts an unsigned 8-bit integer to a hexadecimal string representation.
 *
 * This function takes an unsigned 8-bit integer as input and converts it to a hexadecimal string representation.
 * The returned string is allocated on the heap and should be freed after use.
 *
 * @param w The unsigned 8-bit integer to convert.
 * @return A pointer to the hexadecimal string representation of the input integer.
 */
char * IntToString(int n)
{
    static char ret[24];
    int numChars = 0;
    // Determine if integer is negative
    bool isNegative = false;
    if (n < 0)
    {
        n = -n;
        isNegative = true;
        numChars++;
    }
    // Count how much space we will need for the string
    int temp = n;
    do
    {
        numChars++;
        temp /= 10;
    } while (temp);

    ret[numChars] = 0;
    //Add the negative sign if needed
    if (isNegative)
        ret[0] = '-';
    // Copy digits to string in reverse order
    int i = numChars - 1;
    do
    {
        ret[i--] = n % 10 + '0';
        n /= 10;
    } while (n);
    return ret;
}