#include <net/tcp.h>
#include <net/tcp_impl.h>

union tcp_listen_pcbs_t tcp_listen_pcbs;

struct tcp_pcb *tcp_active_pcbs;

void
tcp_abort(struct tcp_pcb *pcb)
{
  tcp_abandon(pcb, 1);
}