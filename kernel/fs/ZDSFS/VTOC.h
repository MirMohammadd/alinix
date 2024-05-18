#ifndef __ALINIX_KERNEL_V_TOC_H
#define __ALINIX_KERNEL_V_TOC_H


#include <alinix/types.h>

struct DSCB1{
    unsigned char * ds1fmtid;
    uint16_t ds1dsnam;
    uint16_t start_cc;
    uint16_t start_hh;
    
};


#endif