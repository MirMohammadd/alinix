/**
 * @author Ali Mirmohammad
 * @file directorylisting.c
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
 * 	- Provides the listing directory ability.
*/


#include <alinix/system.h>
#include <alinix/listings/directorylisting.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Provides the listing directory ability.")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")

/**
 * Begin listing files in a directory.
 *
 * @param thread Pointer to the thread structure.
 * @param pathPtr Pointer to the path string.
 *
 * @note This function begins listing files in a directory specified by the `path` parameter.
 *       It takes a pointer to the `Thread` structure and a pointer to the path string as parameters.
 *       The `Thread` structure is used to store information about the thread executing the function.
 *       The `path` parameter is a pointer to the path string, which specifies the directory to list files from.
 *       The function does not return any value.
 *
 * @example
 * // Begin listing files in a directory
 * struct Thread* thread = ...;
 * uint32_t pathPtr = ...;
 * BeginListing(thread, pathPtr);
 *
 * @see EndListing()
 * @see ListNextFile()
 */
int BeginListing(struct Thread* thread, uint32_t pathPtr){
    char* path = (char* )pathPtr;
}