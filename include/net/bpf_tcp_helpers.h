#ifndef __ALINIX_KERNEL_BPF_TCP_HELPERS_H
#define __ALINIX_KERNEL_BPF_TCP_HELPERS_H

#include <alinix/types.h>



#ifndef SOL_TCP
#define SOL_TCP 6
#endif

#ifndef TCP_CA_NAME_MAX
#define TCP_CA_NAME_MAX	16
#endif

struct sock_common {
	unsigned char	skc_state;
	uint16_t		skc_num;
} __attribute__((preserve_access_index));

enum sk_pacing {
	SK_PACING_NONE		= 0,
	SK_PACING_NEEDED	= 1,
	SK_PACING_FQ		= 2,
};


struct sock {
	struct sock_common	__sk_common;
#define sk_state		__sk_common.skc_state
	unsigned long		sk_pacing_rate;
	uint32_t			sk_pacing_status; /* see enum sk_pacing */
} __attribute__((preserve_access_index));



struct inet_sock {
	struct sock		sk;
} __attribute__((preserve_access_index));


struct inet_connection_sock {
	struct inet_sock	  icsk_inet;
	uint8_t			  icsk_ca_state:6,
				  icsk_ca_setsockopt:1,
				  icsk_ca_dst_locked:1;
	struct {
		uint8_t		  pending;
	} icsk_ack;
	uint64_t			  icsk_ca_priv[104 / sizeof(uint64_t)];
} __attribute__((preserve_access_index));

struct request_sock {
	struct sock_common		__req_common;
} __attribute__((preserve_access_index));



struct tcp_sock {
	struct inet_connection_sock	inet_conn;

	uint32_t	rcv_nxt;
	uint32_t	snd_nxt;
	uint32_t	snd_una;
	uint32_t	window_clamp;
	uint8_t	ecn_flags;
	uint32_t	delivered;
	uint32_t	delivered_ce;
	uint32_t	snd_cwnd;
	uint32_t	snd_cwnd_cnt;
	uint32_t	snd_cwnd_clamp;
	uint32_t	snd_ssthresh;
	uint8_t	syn_data:1,	/* SYN includes data */
		syn_fastopen:1,	/* SYN includes Fast Open option */
		syn_fastopen_exp:1,/* SYN includes Fast Open exp. option */
		syn_fastopen_ch:1, /* Active TFO re-enabling probe */
		syn_data_acked:1,/* data in SYN is acked by SYN-ACK */
		save_syn:1,	/* Save headers of SYN packet */
		is_cwnd_limited:1,/* forward progress limited by snd_cwnd? */
		syn_smc:1;	/* SYN includes SMC */
	uint32_t	max_packets_out;
	uint32_t	lsndtime;
	uint32_t	prior_cwnd;
	uint64_t	tcp_mstamp;	/* most recent packet received/sent */
	bool	is_mptcp;
} __attribute__((preserve_access_index));

#endif // __ALINIX_KERNEL_BPF_TCP_HELPERS_H