#ifndef __ALINIX_KERNEL_INET_SOCK_H
#define __ALINIX_KERNEL_INET_SOCK_H

#include <alinix/types.h>

struct ip_options{
    uint32_t addr;
    uint32_t nexthop;
    unsigned char opt_len;
    unsigned char srr;
    unsigned char rr;
    unsigned char ts;
    unsigned char	is_strictroute:1,
			srr_is_hit:1,
			is_changed:1,
			rr_needaddr:1,
			ts_needtime:1,
			ts_needaddr:1;
    unsigned char	router_alert;
	unsigned char	cipso;
	unsigned char	__pad2;
	unsigned char	__data[];
};


#endif 