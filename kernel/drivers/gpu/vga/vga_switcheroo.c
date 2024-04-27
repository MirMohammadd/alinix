#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/fs/fat.h>
#include <alinix/vga_switcheroo.h>


struct vgasr_priv{
    bool active;
    bool delayed_switch_active;
    int registered_clients;
    const struct vga_switcheroo_handler *handler;
};

PRIVATE bool vga_switcheroo_ready(NO_ARGS){
    struct vgasr_priv *priv;
    return !priv->active && priv->registered_clients == 2 && priv->handler;
}
