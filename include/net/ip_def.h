#ifndef __ALINIX_KERNEL_NET_IPDEF_H
#define __ALINIX_KERNEL_NET_IPDEF_H


#include <alinix/types.h>
#include <net/err.h>

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

#endif