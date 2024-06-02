/**
 * @author Ali Mirmohammad
 * @file ip_addr.c
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
 * @abstract:
 *  - Driver for the IP address of the kernel.
 * @todo:
 *  - Implement for C++.
*/

#include <net/ip_addr.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("IP address driver for the kernel")
MODULE_LICENSE("AGPL")
MODULE_VERSION("0.1")


const ip_addr_t ip_addr_any = { IPADDR_ANY };
const ip_addr_t ip_addr_broadcast = { IPADDR_BROADCAST };

/**
 * Check if an IPv4 address is a broadcast address on a given network interface.
 *
 * @param addr The IPv4 address to check.
 * @param netif The network interface to check against.
 *
 * @return 1 if the address is a broadcast address on the given network interface, 0 otherwise.
 *
 * @note This function checks if the given IPv4 address is a broadcast address on the specified network interface.
 *       The function first converts the IPv4 address to an `ip_addr_t` structure.
 *       It then checks if the address is all ones (broadcast) or all zeroes (old school broadcast).
 *       If the address matches the network interface address exactly, it is not a broadcast address.
 *       If the network interface supports broadcast and the address is on the same subnet with host identifier bits all ones,
 *       it is a network broadcast address. Otherwise, it is not a broadcast address.
 *
 * @see ip_addr_t, netif
 */
uint8_t
ip4_addr_isbroadcast(uint32_t addr, const struct netif *netif)
{
  ip_addr_t ipaddr;
  ip4_addr_set_u32(&ipaddr, addr);

  /* all ones (broadcast) or all zeroes (old skool broadcast) */
  if ((~addr == IPADDR_ANY) ||
      (addr == IPADDR_ANY)) {
    return 1;
  /* no broadcast support on this network interface? */
  } else if ((netif->flags & NETIF_FLAG_BROADCAST) == 0) {
    /* the given address cannot be a broadcast address
     * nor can we check against any broadcast addresses */
    return 0;
  /* address matches network interface address exactly? => no broadcast */
  } else if (addr == ip4_addr_get_u32(&netif->ip_addr)) {
    return 0;
  /*  on the same (sub) network... */
  } else if (ip_addr_netcmp(&ipaddr, &(netif->ip_addr), &(netif->netmask))
         /* ...and host identifier bits are all ones? =>... */
          && ((addr & ~ip4_addr_get_u32(&netif->netmask)) ==
           (IPADDR_BROADCAST & ~ip4_addr_get_u32(&netif->netmask)))) {
    /* => network broadcast address */
    return 1;
  } else {
    return 0;
  }
}