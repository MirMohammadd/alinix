#ifndef _HEISEN_OS_USB3_HPP__
#define _HEISEN_OS_USB3_HPP__

#include "types.h"
#include "llist.h"
#include "xhci.h"


#if !defined(__cplusplus)
#define true 1
#define false 0

typedef enum { false=0, true } bool_t;
#endif

#if defined(__cplusplus)

namespace LIBHeisenKernel{
    class USB3{
        public:
            USB3();
            ~USB3();
        
        public :
            void Init();
            void Detect();
         
    };
};

#else 

typedef struct {
    bool initialised;
    bool is_csz_64;
    list_t *slot_list;
    xhci_cap_regs_t* caps_reg;
    xhci_op_regs_t* op_regs;
    xhci_doorbell_regs_t* db_regs;
    xhci_runtime_regs_t* rt_regs;
    xhci_ext_cap_t* ext_cap;
    xhci_port_regs_t* ports;
    uint32_t num_slots;
    uint32_t num_ports;
    uint16_t max_intrs;
    uint8_t irq;
    uint64_t* dev_ctx_base_array;
    xhci_trb_t* cmd_ring;
    uint64_t cmd_ring_phys;
    unsigned cmd_ring_index;
    unsigned cmd_ring_max;
    unsigned cmd_ring_cycle;
    uint64_t* event_ring_segment;
    uint64_t* event_ring_seg_phys;
    unsigned evnt_ring_index;
	unsigned evnt_ring_cycle;
	unsigned evnt_ring_max;
	int poll_event_for_trb;
	bool event_available;
	int poll_return_trb_type;
	int trb_event_index;
    Spinlock *usb_lock;
}USBDevice;

#endif

#endif // _HEISEN_OS_USB3_HPP__