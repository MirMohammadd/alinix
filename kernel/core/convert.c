/**
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