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
#include <net/netif.h>
#include <net/opt.h>
#include <net/etharp.h>

#define NETIF_STATUS_CALLBACK(n)


void netif_set_down(struct netif *netif)
{
  if (netif->flags & NETIF_FLAG_UP) {
    netif->flags &= ~NETIF_FLAG_UP;
#if LWIP_SNMP
    snmp_get_sysuptime(&netif->ts);
#endif

#if LWIP_ARP
    if (netif->flags & NETIF_FLAG_ETHARP) {
      etharp_cleanup_netif(netif);
    }
#endif /* LWIP_ARP */
    NETIF_STATUS_CALLBACK(netif);
  }
}
