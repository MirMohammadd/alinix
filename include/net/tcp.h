#ifndef __ALINIX_KERNEL_NET_TCP_H
#define __ALINIX_KERNEL_NET_TCP_H

#include <alinix/types.h>
#include <alinix/ip.h>


#define TCP_PCB_COMMON(type) \
  type *next; /* for the linked list */ \
  void *callback_arg; \
  /* the accept callback for listen- and normal pcbs, if LWIP_CALLBACK_API */ \
  DEF_ACCEPT_CALLBACK \
  enum tcp_state state; /* TCP state */ \
  u8_t prio; \
  /* ports are in host byte order */ \
  u16_t local_port

struct tcp_pcb {
/** common PCB members */
  IP_PCB;
/** protocol specific PCB members */
  TCP_PCB_COMMON(struct tcp_pcb);

  /* ports are in host byte order */
  uint16_t remote_port;
  
  uint8_t flags;
#define TF_ACK_DELAY   ((uint8_t)0x01U)   /* Delayed ACK. */
#define TF_ACK_NOW     ((uint8_t)0x02U)   /* Immediate ACK. */
#define TF_INFR        ((uint8_t)0x04U)   /* In fast recovery. */
#define TF_TIMESTAMP   ((uint8_t)0x08U)   /* Timestamp option enabled */
#define TF_RXCLOSED    ((uint8_t)0x10U)   /* rx closed by tcp_shutdown */
#define TF_FIN         ((uint8_t)0x20U)   /* Connection was closed locally (FIN segment enqueued). */
#define TF_NODELAY     ((uint8_t)0x40U)   /* Disable Nagle algorithm */
#define TF_NAGLEMEMERR ((uint8_t)0x80U)   /* nagle enabled, memerr, try to output to prevent delayed ACK to happen */

  /* the rest of the fields are in host byte order
     as we have to do some math with them */

  /* Timers */
  uint8_t polltmr, pollinterval;
  uint8_t last_timer;
  uint32_t tmr;

  /* receiver variables */
  uint32_t rcv_nxt;   /* next seqno expected */
  uint16_t rcv_wnd;   /* receiver window available */
  uint16_t rcv_ann_wnd; /* receiver window to announce */
  uint32_t rcv_ann_right_edge; /* announced right edge of window */

  /* Retransmission timer. */
  sint16_t rtime;

  uint16_t mss;   /* maximum segment size */

  /* RTT (round trip time) estimation variables */
  uint32_t rttest; /* RTT estimate in 500ms ticks */
  uint32_t rtseq;  /* sequence number being timed */
  sint16_t sa, sv; /* @todo document this */

  sint16_t rto;    /* retransmission time-out */
  uint8_t nrtx;    /* number of retransmissions */

  /* fast retransmit/recovery */
  uint8_t dupacks;
  uint32_t lastack; /* Highest acknowledged seqno. */

  /* congestion avoidance/control variables */
  uint16_t cwnd;
  uint16_t ssthresh;

  /* sender variables */
  uint32_t snd_nxt;   /* next new seqno to be sent */
  uint32_t snd_wl1, snd_wl2; /* Sequence and acknowledgement numbers of last
                             window update. */
  uint32_t snd_lbb;       /* Sequence number of next byte to be buffered. */
  uint16_t snd_wnd;   /* sender window */
  uint16_t snd_wnd_max; /* the maximum sender window announced by the remote host */

  uint16_t acked;

  uint16_t snd_buf;   /* Available buffer space for sending (in bytes). */
#define TCP_SNDQUEUELEN_OVERFLOW (0xffffU-3)
  uint16_t snd_queuelen; /* Available buffer space for sending (in tcp_segs). */

#if TCP_OVERSIZE
  /* Extra bytes available at the end of the last pbuf in unsent. */
  uint16_t unsent_oversize;
#endif /* TCP_OVERSIZE */ 

  /* These are ordered by sequence number: */
  struct tcp_seg *unsent;   /* Unsent (queued) segments. */
  struct tcp_seg *unacked;  /* Sent but unacknowledged segments. */
#if TCP_QUEUE_OOSEQ  
  struct tcp_seg *ooseq;    /* Received out of sequence segments. */
#endif /* TCP_QUEUE_OOSEQ */

  struct pbuf *refused_data; /* Data previously received but not yet taken by upper layer */

#if LWIP_CALLBACK_API
  /* Function to be called when more send buffer space is available. */
  tcp_sent_fn sent;
  /* Function to be called when (in-sequence) data has arrived. */
  tcp_recv_fn recv;
  /* Function to be called when a connection has been set up. */
  tcp_connected_fn connected;
  /* Function which is called periodically. */
  tcp_poll_fn poll;
  /* Function to be called whenever a fatal error occurs. */
  tcp_err_fn errf;
#endif /* LWIP_CALLBACK_API */

#if LWIP_TCP_TIMESTAMPS
  uint32_t ts_lastacksent;
  uint32_t ts_recent;
#endif /* LWIP_TCP_TIMESTAMPS */

  /* idle time before KEEPALIVE is sent */
  uint32_t keep_idle;
#if LWIP_TCP_KEEPALIVE
  uint32_t keep_intvl;
  uint32_t keep_cnt;
#endif /* LWIP_TCP_KEEPALIVE */
  
  /* Persist timer counter */
  uint8_t persist_cnt;
  /* Persist timer back-off */
  uint8_t persist_backoff;

  /* KEEPALIVE counter */
  uint8_t keep_cnt_sent;
};


#endif