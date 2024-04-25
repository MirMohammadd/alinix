#ifndef __ALINIX_KERNEL_NET_TYPING_H
#define __ALINIX_KERNEL_NET_TYPING_H

#include <net/ip_addr.h>
#include <net/err.h>
#include <alinix/compiler.h>

// Define the structures
struct ip_addr {
    uint32_t addr;
};

struct ip_addr_packed {
    uint32_t addr;
};

// Define the typedefs
typedef struct ip_addr ip_addr_t;
typedef struct ip_addr_packed ip_addr_p_t;

typedef err_t *netif_init_fn;

typedef err_t *netif_input_fn;

typedef err_t *netif_output_fn;


typedef err_t *netif_linkoutput_fn;
/** Function prototype for netif status- or link-callback functions. */


#endif // __ALINIX_KERNEL_NET_TYPING_H