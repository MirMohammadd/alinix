#include <net/netif.h>
#include <net/opt.h>

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
