#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/fs/fat.h>
#include <alinix/vga_switcheroo.h>
#include <alinix/pci.h>
#include <alinix/ulib.h>
#include <alinix/memory.h>

#define GFP_KERNEL 0

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

struct vga_switcheroo_client {
	struct pci_dev *pdev;
	struct fb_info *fb_info;
	const struct vga_switcheroo_client_ops *ops;
	enum vga_switcheroo_client_id id;
	bool active;
	bool driver_power_control;
	struct list_head list;
	struct pci_dev *vga_dev;
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

PRIVATE int register_client(struct pci_dev *pdev,
			   const struct vga_switcheroo_client_ops *ops,
			   enum vga_switcheroo_client_id id,
			   struct pci_dev *vga_dev,
			   bool active,
			   bool driver_power_control){
            
        struct vga_switcheroo_client *client;
        memset(client,GFP_KERNEL,sizeof(struct vga_switcheroo_client));
        if (!client)
            return -ENOMEM;
            
        // client->pwr_state = VGA_SWITCHEROO_ON;
        client->pdev = pdev;
        client->ops = ops;
        client->id = id;
        client->active = active;
        client->driver_power_control = driver_power_control;
        client->vga_dev = vga_dev;

        return 0;
}


int vga_switcheroo_register_client(struct pci_dev *pdev,
				   const struct vga_switcheroo_client_ops *ops,
				   bool driver_power_control){
            return register_client(pdev, ops, VGA_SWITCHEROO_UNKNOWN_ID, NULL,
            pdev == vga_default_device(),
            driver_power_control);
            }


int main(){
    return 0;
}