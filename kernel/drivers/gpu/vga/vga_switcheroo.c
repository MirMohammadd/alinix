#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/fs/fat.h>


struct vgasr_priv{
    bool active;
    bool delayed_switch_active;
    int registered_clients;
    
};

PRIVATE bool vga_switcheroo_ready(NO_ARGS){

}
