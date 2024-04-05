#ifndef _HEISEN_KERNEL_XHCI__
#define _HEISEN_KERNEL_XHCI__

#if defined(__cplusplus)
#include "types.h"
using namespace LIBHeisenKernel;

#else 
#include <stdint.h>

#endif 



#pragma pack(push,1)
typedef struct _xhci_doorbell_ {
	unsigned doorbell[256];
}xhci_doorbell_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_cap_regs_ {
	uint8_t cap_caplen_version;
	uint8_t reserved;
	uint16_t hci_version;
	uint32_t cap_hcsparams1;
	uint32_t cap_hcsparams2;
	uint32_t cap_hcsparams3;
	uint32_t cap_hccparams1;
	uint32_t cap_dboff;
	uint32_t cap_hccparams2;
}xhci_cap_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_cap_regs_ {
	uint8_t cap_caplen_version;
	uint8_t reserved;
	uint16_t hci_version;
	uint32_t cap_hcsparams1;
	uint32_t cap_hcsparams2;
	uint32_t cap_hcsparams3;
	uint32_t cap_hccparams1;
	uint32_t cap_dboff;
	uint32_t cap_hccparams2;
}xhci_cap_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_ex_cap_ {
	uint32_t id : 8;
	uint32_t next : 8;
	uint32_t controller_bios_semaphore : 1;
	uint32_t rsvd : 7;
	uint32_t controller_os_sem : 1;
	uint32_t rsvd2 : 7;
}xhci_ext_cap_t;
#pragma pack(pop)

typedef struct _xhci_op_regs_ {
	uint32_t op_usbcmd;
	uint32_t op_usbsts;
	uint32_t op_pagesize;
	uint32_t op_pad1[2];
	uint32_t op_dnctrl;
	uint64_t op_crcr;
	uint32_t op_pad2[4];
	uint32_t op_dcbaap_lo;
	uint32_t op_dcbaap_hi;
	uint32_t op_config;
}xhci_op_regs_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_intr_reg_ {
	unsigned intr_man;
	unsigned intr_mod;
	unsigned evtRngSegTabSz;
	unsigned res;
	unsigned evtRngSegBaseLo;
	unsigned evtRngSegBaseHi;
	unsigned evtRngDeqPtrLo;
	unsigned evtRngDeqPtrHi;
}xhci_interrupter_reg_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _xhci_runtime_regs_ {
	unsigned micro_frame_index;
	char res[28];
	xhci_interrupter_reg_t intr_reg[];
}xhci_runtime_regs_t;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct _xhci_port_reg_ {
	uint32_t port_sc;
	uint32_t port_pmsc;
	uint32_t port_link_info;
	uint32_t port_hardware_LMP_ctl;
}xhci_port_regs_t;
#pragma pack(pop)


#endif