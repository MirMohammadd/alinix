#ifndef __ALINIX_KERNEL_V_TOC_H
#define __ALINIX_KERNEL_V_TOC_H


#include <alinix/types.h>

struct DSCB1{
    unsigned char * ds1fmtid;
    uint16_t ds1dsnam;
    uint16_t start_cc;
    uint16_t start_hh;

};

void GetCHRFromVTOC(void *buffer);
void CheckDSCB(struct DSCB1 *dscb, const char *name);
void FindFile(const char *name) ;

#endif