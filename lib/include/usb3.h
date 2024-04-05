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
}USBDevice;

#endif

#endif // _HEISEN_OS_USB3_HPP__