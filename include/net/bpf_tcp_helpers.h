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

#endif // __ALINIX_KERNEL_BPF_TCP_HELPERS_H