/**
 * @author Ali Mirmohammad
 * @file def.c
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
#include <alinix/types.h>
#include <net/def.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("A simple module to test the module system for networking.")
MODULE_LICENSE("AGPL3")
MODULE_VERSION("0.1")

/**
 * @abstraction:
 *  - stuff for the ipv4 drivers.
*/

/**
 * @brief Converts a 16-bit integer from host byte order to network byte order.
 * 
 * This function takes a 16-bit integer in host byte order and converts it 
 * to network byte order (big-endian) by swapping the byte order.
 * 
 * @param n The 16-bit integer in host byte order to convert.
 * @return The 16-bit integer in network byte order (big-endian).
 */

uint16_t
lwip_htons(uint16_t n)
{
  return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}
/**
 * @brief Converts a 32-bit integer from network byte order to host byte order.
 * 
 * This function takes a 32-bit integer in network byte order (big-endian) and converts it 
 * to host byte order by calling the lwip_htonl function to swap the byte order.
 * 
 * @param n The 32-bit integer in network byte order to convert.
 * @return The 32-bit integer in host byte order.
 */

uint32_t
lwip_ntohl(uint32_t n)
{
  return lwip_htonl(n);
}
