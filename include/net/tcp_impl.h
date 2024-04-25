#ifndef __ALINIX_KERNEL_NET_TCP_IMPL_H
#define __ALINIX_KERNEL_NET_TCP_IMPL_H

#include <alinix/types.h>
#include <net/tcp.h>

extern union tcp_listen_pcbs_t tcp_listen_pcbs;

extern uint8_t tcp_active_pcbs_changed;
extern struct tcp_pcb *tcp_active_pcbs;  /* List of all TCP PCBs that are in a
              state in which they accept or send
              data. */


union tcp_listen_pcbs_t { /* List of all TCP PCBs in LISTEN state. */
  struct tcp_pcb_listen *listen_pcbs; 
  struct tcp_pcb *pcbs;
};
#endif