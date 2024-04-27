#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/fs/fat.h>
#include <alinix/vga_switcheroo.h>

#define ID_BIT_AUDIO		0x100
#define client_is_audio(c)		((c)->id & ID_BIT_AUDIO)
#define client_is_vga(c)		(!client_is_audio(c))

struct vgasr_priv{
    bool active;
    bool delayed_switch_active;
    int registered_clients;
    const struct vga_switcheroo_handler *handler;
    enum vga_switcheroo_client_id id;
};

PRIVATE bool vga_switcheroo_ready(NO_ARGS){
    struct vgasr_priv *priv;
    return !priv->active && priv->registered_clients == 2 && priv->handler;
}

PRIVATE VOID vga_switcheroo_enable(NO_ARGS){
    int ret;
    struct vgasr_priv *priv;
    struct vga_switcheroo_enable *client;
    if (priv->handler->init)
        priv->handler->init();

    
    priv->active = true;
}
