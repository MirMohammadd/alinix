#ifndef __ALINIX_KERNEL_USB_H
#define __ALINIX_KERNEL_USB_H

#include <alinix/kernel.h>

struct usb_device {
	int		devnum;
	char		devpath[16];
	u32		route;
	// enum usb_device_state	state;
	// enum usb_device_speed	speed;
	unsigned int		rx_lanes;
	unsigned int		tx_lanes;
	// enum usb_ssp_rate	ssp_rate;

	// struct usb_tt	*tt;
	int		ttport;

	unsigned int toggle[2];

	struct usb_device *parent;
	// struct usb_bus *bus;
	// struct usb_host_endpoint ep0;

	struct device dev;

	// struct usb_device_descriptor descriptor;
	// struct usb_host_bos *bos;
	// struct usb_host_config *config;

	// struct usb_host_config *actconfig;
	// struct usb_host_endpoint *ep_in[16];
	// struct usb_host_endpoint *ep_out[16];

	char **rawdescriptors;

	unsigned short bus_mA;
	u8 portnum;
	u8 level;
	u8 devaddr;

	unsigned can_submit:1;
	unsigned persist_enabled:1;
	unsigned reset_in_progress:1;
	unsigned have_langid:1;
	unsigned authorized:1;
	unsigned authenticated:1;
	unsigned lpm_capable:1;
	unsigned lpm_devinit_allow:1;
	unsigned usb2_hw_lpm_capable:1;
	unsigned usb2_hw_lpm_besl_capable:1;
	unsigned usb2_hw_lpm_enabled:1;
	unsigned usb2_hw_lpm_allowed:1;
	unsigned usb3_lpm_u1_enabled:1;
	unsigned usb3_lpm_u2_enabled:1;
	int string_langid;

	/* static strings from the device */
	char *product;
	char *manufacturer;
	char *serial;

	struct list_head filelist;

	int maxchild;

	u32 quirks;
	atomic_t urbnum;

	unsigned long active_duration;

	unsigned long connect_time;

	unsigned do_remote_wakeup:1;
	unsigned reset_resume:1;
	unsigned port_is_suspended:1;

	int slot_id;
	// struct usb2_lpm_parameters l1_params;
	// struct usb3_lpm_parameters u1_params;
	// struct usb3_lpm_parameters u2_params;
	unsigned lpm_disable_count;

	u16 hub_delay;
	unsigned use_generic_driver:1;
};

#endif // __ALINIX_KERNEL_USB_H