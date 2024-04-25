#include <net/tcp.h>
#include <net/tcp_impl.h>
#include <alinix/types.h>
#include <net/err.h>
#include <net/ip_addr.h>

struct tcp_pcb *tcp_tw_pcbs;

enum tcp_state {
  CLOSED      = 0,
  LISTEN      = 1,
  SYN_SENT    = 2,
  SYN_RCVD    = 3,
  ESTABLISHED = 4,
  FIN_WAIT_1  = 5,
  FIN_WAIT_2  = 6,
  CLOSE_WAIT  = 7,
  CLOSING     = 8,
  LAST_ACK    = 9,
  TIME_WAIT   = 10
};

union tcp_listen_pcbs_t tcp_listen_pcbs;

struct tcp_pcb *tcp_active_pcbs;

void
tcp_abort(struct tcp_pcb *pcb)
{
  tcp_abandon(pcb, 1);
}

void
tcp_abandon(struct tcp_pcb *pcb, int reset)
{
  uint32_t seqno, ackno;
#if LWIP_CALLBACK_API  
  tcp_err_fn errf;
#endif /* LWIP_CALLBACK_API */
  void *errf_arg;

  /* pcb->state LISTEN not allowed here */
  /* Figure out on which TCP PCB list we are, and remove us. If we
     are in an active state, call the receive function associated with
     the PCB with a NULL argument, and send an RST to the remote end. */
  if (pcb->state == TIME_WAIT) {
    tcp_pcb_remove(&tcp_tw_pcbs, pcb);
    memp_free(MEMP_DEBUG, pcb);
  } else {
    seqno = pcb->snd_nxt;
    ackno = pcb->rcv_nxt;
#if LWIP_CALLBACK_API
    errf = pcb->errf;
#endif /* LWIP_CALLBACK_API */
    errf_arg = pcb->callback_arg;
    TCP_PCB_REMOVE_ACTIVE(pcb);
    if (pcb->unacked != NULL) {
      tcp_segs_free(pcb->unacked);
    }
    if (pcb->unsent != NULL) {
      tcp_segs_free(pcb->unsent);
    }
#if TCP_QUEUE_OOSEQ    
    if (pcb->ooseq != NULL) {
      tcp_segs_free(pcb->ooseq);
    }
#endif /* TCP_QUEUE_OOSEQ */
    if (reset) {
      LWIP_DEBUGF(TCP_RST_DEBUG, ("tcp_abandon: sending RST\n"));
    }
    memp_free(MEMP_DEBUG, pcb);
    TCP_EVENT_ERR(errf, errf_arg, ERR_ABRT);
  }
}