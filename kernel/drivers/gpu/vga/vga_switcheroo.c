/**
 * @author Ali Mirmohammad
 * @file vga_switcheroo.c
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 * 	- Provide common functions over the VGA.
*/


#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/fs/fat.h>
#include <alinix/vga_switcheroo.h>
#include <alinix/pci.h>
#include <alinix/ulib.h>
#include <alinix/memory.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("VGA Switcheroo")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

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

/**
 * Check if VGA switcheroo is ready.
 *
 * This function checks if the VGA switcheroo system is ready for use. It checks
 * if the following conditions are met:
 *
 * - The VGA switcheroo system is not currently active.
 * - There are exactly two registered clients.
 * - A handler function is registered.
 *
 * @return true if VGA switcheroo is ready, false otherwise.
 */
PRIVATE bool vga_switcheroo_ready(NO_ARGS){
    struct vgasr_priv *priv;
    return !priv->active && priv->registered_clients == 2 && priv->handler;
}

/**
 * Enable VGA switcheroo.
 *
 * This function enables the VGA switcheroo system. It performs the following steps:
 *
 * 1. If a handler function is registered and it has an `init` function, it calls the `init` function.
 * 2. Sets the `active` flag to indicate that VGA switcheroo is enabled.
 *
 * Note: This function assumes that the `vgasr_priv` struct and the `vga_switcheroo_enable` struct are defined elsewhere in the codebase.
 *
 * @return void
 */
PRIVATE VOID vga_switcheroo_enable(NO_ARGS){
    int ret;
    struct vgasr_priv *priv;
    struct vga_switcheroo_enable *client;
    if (priv->handler->init)
        priv->handler->init();

    
    priv->active = true;
}

/**
 * Register a VGA switcheroo client.
 *
 * This function registers a client for the VGA switcheroo system. It performs the following steps:
 *
 * 1. Allocates memory for the `struct vga_switcheroo_client` structure.
 * 2. Initializes the `struct vga_switcheroo_client` structure with the provided parameters.
 * 3. Returns 0 on success, or -ENOMEM if memory allocation fails.
 *
 * @param pdev The PCI device associated with the client.
 * @param ops The client operations structure.
 * @param id The client ID.
 * @param vga_dev The VGA device associated with the client.
 * @param active Indicates whether the client is active.
 * @param driver_power_control Indicates whether the client has power control.
 *
 * @return 0 on success, or -ENOMEM if memory allocation fails.
 */


/**
 * Register a VGA switcheroo client.
 *
 * This function registers a client for the VGA switcheroo system. It performs the following steps:
 *
 * 1. Allocates memory for the `struct vga_switcheroo_client` structure.
 * 2. Initializes the `struct vga_switcheroo_client` structure with the provided parameters.
 * 3. Returns 0 on success, or -ENOMEM if memory allocation fails.
 *
 * @param pdev The PCI device associated with the client.
 * @param ops The client operations structure.
 * @param id The client ID.
 * @param vga_dev The VGA device associated with the client.
 * @param active Indicates whether the client is active.
 * @param driver_power_control Indicates whether the client has power control.
 *
 * @return 0 on success, or -ENOMEM if memory allocation fails.
 */
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


/**
 * Register a VGA switcheroo client with the VGA switcheroo system.
 *
 * This function registers a client for the VGA switcheroo system. It performs the following steps:
 *
 * 1. Calls the `register_client` function with the provided parameters, including the `VGA_SWITCHEROO_UNKNOWN_ID` for the client ID and `NULL` for the VGA device.
 * 2. Sets the `active` flag to `true` if the `pdev` parameter is equal to 1.
 * 3. Returns the result of the `register_client` function.
 *
 * @param pdev The PCI device associated with the client.
 * @param ops The client operations structure.
 * @param driver_power_control Indicates whether the client has power control.
 *
 * @return The result of the `register_client` function.
 */
int vga_switcheroo_register_client(struct pci_dev *pdev,
				   const struct vga_switcheroo_client_ops *ops,
				   bool driver_power_control){
            return register_client(pdev, ops, VGA_SWITCHEROO_UNKNOWN_ID, NULL,
            pdev == 1,
            driver_power_control);
            }


int main(){
    return 0;
}