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

#endif // __ALINIX_KERNEL_BPF_TCP_HELPERS_H