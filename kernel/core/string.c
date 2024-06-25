/**
 * @author Ali Mirmohammad
 * @file string.c
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
 *  - Provides abstraction for string operations.
*/

#include <alinix/string.h>
#include <alinix/types.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("String operations")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


/**
 * Get the length of a null-terminated string.
 *
 * This function calculates the length of a null-terminated string by iterating over its characters.
 * It performs the following steps:
 *
 * 1. Initializes a variable `len` to 0.
 * 2. Iterates over each character in the string until a null character is encountered.
 * 3. Increments the `len` variable by 1 for each character encountered.
 * 4. Returns the final value of `len`, which represents the length of the string.
 *
 * @param str The null-terminated string for which to calculate the length.
 *
 * @return The length of the string.
 */
int strlen(const char* str){
    uint32_t len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

/**
 * Compare two null-terminated strings for equality.
 *
 * This function compares two null-terminated strings character by character and returns true if they are equal, false otherwise.
 * It performs the following steps:
 *
 * 1. Iterates over each character in both strings simultaneously.
 * 2. Compares each character from both strings.
 * 3. If a pair of characters is not equal, the function returns false.
 * 4. If a null character is encountered in either string, the function returns true.
 * 5. If the entire strings are compared and no inequality is found, the function returns true.
 *
 * @param strA The first null-terminated string to compare.
 * @param strB The second null-terminated string to compare.
 *
 * @return true if the strings are equal, false otherwise.
 */
bool strcmp(const char* strA,const char* strB){
    while (*strA == *strB){
        if (*strA == '\0'){
            return true;
        strA++;
        strB++;
        }
    }
    return false;
}

/**
 * Find the index of the nth occurrence of a character in a null-terminated string.
 *
 * This function searches for the nth occurrence of a specified character in a null-terminated string and returns its index.
 * It performs the following steps:
 *
 * 1. Initializes a variable `hits` to 0 to keep track of the number of occurrences found so far.
 * 2. Initializes a variable `i` to 0 to iterate over each character in the string.
 * 3. Iterates over each character in the string until a null character is encountered.
 * 4. If the current character is equal to the specified character and the number of occurrences found is equal to the skip value, the function returns the current index.
 * 5. If the entire string is searched and the specified character is not found, the function returns -1.
 *
 * @param str The null-terminated string to search in.
 * @param c The character to search for.
 * @param skip The index of the occurrence to find (0-based).
 *
 * @return The index of the nth occurrence of the character in the string, or -1 if the character is not found.
 */
int IndexOf(const char* str, char c, uint32_t skip){
    uint32_t hits = 0;
    int i = 0;
    while(str[i])
    {
        if(str[i] == c && hits++ == skip)
            return i;
        i++;
    }
    return -1;
}

/**
 * Check if a null-terminated string contains a specified character.
 *
 * This function checks if a null-terminated string contains a specified character and returns true if it does, false otherwise.
 * It performs the following steps:
 *
 * 1. Initializes a variable `i` to 0 to iterate over each character in the string.
 * 2. Iterates over each character in the string until a null character is encountered.
 * 3. If the current character is equal to the specified character, the function returns true.
 * 4. If the entire string is searched and the specified character is not found, the function returns false.
 *
 * @param str The null-terminated string to search in.
 * @param c The character to search for.
 *
 * @return true if the string contains the specified character, false otherwise.
 */
bool Contains(const char* str, char c){
    int i = 0;
	while (str[i])
    {
        if(str[i] == c)
            return true;
		i++;
    }
    return false;
}

/**
 * Convert a null-terminated string to uppercase.
 *
 * This function converts a null-terminated string to uppercase by modifying the characters in the string.
 * It performs the following steps:
 *
 * 1. Calculates the length of the input string using the `strlen` function.
 * 2. Iterates over each character in the string.
 * 3. If the current character is within the range of lowercase ASCII characters (97-122), it subtracts 32 to convert it to uppercase.
 * 4. Returns the modified string.
 *
 * @param str The null-terminated string to convert to uppercase.
 *
 * @return The modified string with uppercase characters.
 */
char* Uppercase(char* str){
    int len = strlen(str);
    int i = 0;
	while (i < len)
	{
		if ((short)str[i] >= 97 && (short)str[i] <= 122)
			str[i] -= 32;
		i++;
	}
    return str;
}

/**
 * Convert a null-terminated string to lowercase.
 *
 * This function converts a null-terminated string to lowercase by modifying the characters in the string.
 * It performs the following steps:
 *
 * 1. Calculates the length of the input string using the `strlen` function.
 * 2. Iterates over each character in the string.
 * 3. If the current character is within the range of uppercase ASCII characters (65-90), it adds 32 to convert it to lowercase.
 * 4. Returns the modified string.
 *
 * @param str The null-terminated string to convert to lowercase.
 *
 * @return The modified string with lowercase characters.
 */
char* Lowercase(char* str)
{
    int len = strlen(str);
    int i = 0;
	while (i < len)
	{
		if ((short)str[i] >= 65 && (short)str[i] <= 90)
			str[i] += 32;
		i++;
	}
    return str;
}


/**
 * Copy a null-terminated string from one character array to another.
 *
 * This function copies a null-terminated string from the source character array `s2` to the destination character array `s1`.
 * It performs the following steps:
 *
 * 1. Calls the `strncpy` function to copy the characters from `s2` to `s1`.
 * 2. If the null terminating character is not already present in `s2`, it manually adds it to `s1`.
 * 3. Returns the destination character array `s1`.
 *
 * @param s1 The destination character array where the string will be copied to.
 * @param s2 The source character array from where the string will be copied.
 *
 * @return The destination character array `s1` after the copy operation.
 */
char* strcpy(char *s1, const char *s2)
{
	strncpy(s1, s2, strlen(s2) + 1);
	s1[strlen(s2)] = '\0'; //tack on the null terminating character if it wasn't already done
	return s1;
}

/**
 * Copy a maximum of `n` characters from a null-terminated string from one character array to another.
 *
 * This function copies a maximum of `n` characters from the source character array `s2` to the destination character array `s1`.
 * It performs the following steps:
 *
 * 1. Iterates through `s2` up to `n` characters, copying them to `s1`.
 * 2. If the end of `s2` is found before `n` characters, the null terminating character is copied and the external iterator is updated.
 * 3. If there are still spaces remaining in `s1`, they are filled with null characters.
 * 4. Returns the destination character array `s1` after the copy operation.
 *
 * @param s1 The destination character array where the string will be copied to.
 * @param s2 The source character array from where the string will be copied.
 * @param n The maximum number of characters to copy.
 *
 * @return The destination character array `s1` after the copy operation.
 */
char* strncpy(char *s1, const char *s2, unsigned int n)
{
	unsigned int extern_iter = 0;

	unsigned int iterator = 0;
	for (iterator = 0; iterator < n; iterator++) //iterate through s2 up to char n, copying them to s1
	{
		if (s2[iterator] != '\0')
			s1[iterator] = s2[iterator];
		else //the end of s2 was found prematurely - copy the null character, update external iterator and quit for loop
		{
			s1[iterator] = s2[iterator];
			extern_iter = iterator + 1;
			break;
		}
	}

	while (extern_iter < n) //while there are still spaces that need to be filled with null characters, fill them
	{
		s1[extern_iter] = '\0';
		extern_iter++;
	}

	return s1;
}