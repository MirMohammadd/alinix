/**
 * @file hci_core.h
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
 * 	- Bluetooth header file for ath3k.c.
*/


#ifndef __ALINIX_KERNEL_HCI_CORE_H
#define __ALINIX_KERNEL_HCI_CORE_H

#include <alinix/kernel.h>
#include <alinix/mutex_types.h>
#include "bluetooth.h"

#define HCI_MAX_NAME_LENGTH		248
#define HCI_MAX_SHORT_NAME_LENGTH 10
#define HCI_MAX_EIR_LENGTH 7
#define HCI_OP_WRITE_LOCAL_NAME		0x0c13

struct hci_dev {
	struct list_head list;
	struct mutex	lock;

	// struct ida	unset_handle_ida;

	const char	*name;
	unsigned long	flags;
	u16		id;
	u8		bus;
	u8		dev_type;
	bdaddr_t	bdaddr;
	bdaddr_t	setup_addr;
	bdaddr_t	public_addr;
	bdaddr_t	random_addr;
	bdaddr_t	static_addr;
	u8		adv_addr_type;
	u8		dev_name[HCI_MAX_NAME_LENGTH];
	u8		short_name[HCI_MAX_SHORT_NAME_LENGTH];
	u8		eir[HCI_MAX_EIR_LENGTH];
	u16		appearance;
	u8		dev_class[3];
	u8		major_class;
	u8		minor_class;
	u8		max_page;
	u8		features[7][8];
	u8		le_features[8];
	u8		le_accept_list_size;
	u8		le_resolv_list_size;
	u8		le_num_of_adv_sets;
	u8		le_states[8];
	u8		mesh_ad_types[16];
	u8		mesh_send_ref;
	u8		commands[64];
	u8		hci_ver;
	u16		hci_rev;
	u8		lmp_ver;
	u16		manufacturer;
	u16		lmp_subver;
	u16		voice_setting;
	u8		num_iac;
	u16		stored_max_keys;
	u16		stored_num_keys;
	u8		io_capability;
	sint8_t		inq_tx_power;
	u8		err_data_reporting;
	u16		page_scan_interval;
	u16		page_scan_window;
	u8		page_scan_type;
	u8		le_adv_channel_map;
	u16		le_adv_min_interval;
	u16		le_adv_max_interval;
	u8		le_scan_type;
	u16		le_scan_interval;
	u16		le_scan_window;
	u16		le_scan_int_suspend;
	u16		le_scan_window_suspend;
	u16		le_scan_int_discovery;
	u16		le_scan_window_discovery;
	u16		le_scan_int_adv_monitor;
	u16		le_scan_window_adv_monitor;
	u16		le_scan_int_connect;
	u16		le_scan_window_connect;
	u16		le_conn_min_interval;
	u16		le_conn_max_interval;
	u16		le_conn_latency;
	u16		le_supv_timeout;
	u16		le_def_tx_len;
	u16		le_def_tx_time;
	u16		le_max_tx_len;
	u16		le_max_tx_time;
	u16		le_max_rx_len;
	u16		le_max_rx_time;
	u8		le_max_key_size;
	u8		le_min_key_size;
	u16		discov_interleaved_timeout;
	u16		conn_info_min_age;
	u16		conn_info_max_age;
	u16		auth_payload_timeout;
	u8		min_enc_key_size;
	u8		max_enc_key_size;
	u8		pairing_opts;
	u8		ssp_debug_mode;
	u8		hw_error_code;
	u32		clock;
	u16		advmon_allowlist_duration;
	u16		advmon_no_filter_duration;
	u8		enable_advmon_interleave_scan;

	u16		devid_source;
	u16		devid_vendor;
	u16		devid_product;
	u16		devid_version;

	u8		def_page_scan_type;
	u16		def_page_scan_int;
	u16		def_page_scan_window;
	u8		def_inq_scan_type;
	u16		def_inq_scan_int;
	u16		def_inq_scan_window;
	u16		def_br_lsto;
	u16		def_page_timeout;
	u16		def_multi_adv_rotation_duration;
	u16		def_le_autoconnect_timeout;
	sint8_t		min_le_tx_power;
	sint8_t		max_le_tx_power;

	u16		pkt_type;
	u16		esco_type;
	u16		link_policy;
	u16		link_mode;

	u32		idle_timeout;
	u16		sniff_min_interval;
	u16		sniff_max_interval;

	u8		amp_status;
	u32		amp_total_bw;
	u32		amp_max_bw;
	u32		amp_min_latency;
	u32		amp_max_pdu;
	u8		amp_type;
	u16		amp_pal_cap;
	u16		amp_assoc_size;
	u32		amp_max_flush_to;
	u32		amp_be_flush_to;

	// struct amp_assoc	loc_assoc;

	u8		flow_ctl_mode;

	unsigned int	auto_accept_delay;

	unsigned long	quirks;

	atomic_t	cmd_cnt;
	unsigned int	acl_cnt;
	unsigned int	sco_cnt;
	unsigned int	le_cnt;
	unsigned int	iso_cnt;

	unsigned int	acl_mtu;
	unsigned int	sco_mtu;
	unsigned int	le_mtu;
	unsigned int	iso_mtu;
	unsigned int	acl_pkts;
	unsigned int	sco_pkts;
	unsigned int	le_pkts;
	unsigned int	iso_pkts;

	u16		block_len;
	u16		block_mtu;
	u16		num_blocks;
	u16		block_cnt;

	unsigned long	acl_last_tx;
	unsigned long	sco_last_tx;
	unsigned long	le_last_tx;

	u8		le_tx_def_phys;
	u8		le_rx_def_phys;

};

#endif /*__ALINIX_KERNEL_HCI_CORE_H*/