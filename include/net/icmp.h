#ifndef __ALINIX_KERNEL_ICMP_INCLUDED_H
#define __ALINIX_KERNEL_ICMP_INCLUDED_H

#include <alinix/types.h>


struct icmp_err{
    NUMBER errorno;
    POSITIVE fatal:1;
};

EXTERNAL CONSTANT struct icmp_err icmp_err_convert[];



#endif // __ALINIX_KERNEL_ICMP_INCLUDED_H