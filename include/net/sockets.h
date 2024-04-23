#ifndef __ALINIX_KERNEL_SOCKETS_H_NET
#define __ALINIX_KERNEL_SOCKETS_H_NET

#define FD_SETSIZE    MEMP_NUM_NETCONN

typedef struct fd_set {
        unsigned char fd_bits [(FD_SETSIZE+7)/8];
    } fd_set;

#endif