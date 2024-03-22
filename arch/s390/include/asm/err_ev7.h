#ifndef __ALPHA_ERR_EV7_H
#define __ALPHA_ERR_EV7_H 1

#include <heisen/typing.h>

/*
 * Data for el packet class PAL (14), type LOGOUT_FRAME (1)
 */
struct ev7_pal_logout_subpacket {
	uint32_t mchk_code;
	uint32_t subpacket_count;
	uint64_t whami;
	uint64_t rbox_whami;
	uint64_t rbox_int;
	uint64_t exc_addr;
	union el_timestamp timestamp;
	uint64_t halt_code;
	uint64_t reserved;
};

/*
 * Data for el packet class PAL (14), type EV7_PROCESSOR (4)
 */
struct ev7_pal_processor_subpacket {
	uint64_t i_stat;
	uint64_t dc_stat;
	uint64_t c_addr;
	uint64_t c_syndrome_1;
	uint64_t c_syndrome_0;
	uint64_t c_stat;
	uint64_t c_sts;
	uint64_t mm_stat;
	uint64_t exc_addr;
	uint64_t ier_cm;
	uint64_t isum;
	uint64_t pal_base;
	uint64_t i_ctl;
	uint64_t process_context;
	uint64_t cbox_ctl;
	uint64_t cbox_stp_ctl;
	uint64_t cbox_acc_ctl;
	uint64_t cbox_lcl_set;
	uint64_t cbox_gbl_set;
	uint64_t bbox_ctl;
	uint64_t bbox_err_sts;
	uint64_t bbox_err_idx;
	uint64_t cbox_ddp_err_sts;
	uint64_t bbox_dat_rmp;
	uint64_t reserved[2];
};

/*
 * Data for el packet class PAL (14), type EV7_ZBOX (5)
 */
struct ev7_pal_zbox_subpacket {
	uint32_t zbox0_dram_err_status_1;
	uint32_t zbox0_dram_err_status_2;
	uint32_t zbox0_dram_err_status_3;
	uint32_t zbox0_dram_err_ctl;
	uint32_t zbox0_dram_err_adr;
	uint32_t zbox0_dift_timeout;
	uint32_t zbox0_dram_mapper_ctl;
	uint32_t zbox0_frc_err_adr;
	uint32_t zbox0_dift_err_status;
	uint32_t reserved1;
	uint32_t zbox1_dram_err_status_1;
	uint32_t zbox1_dram_err_status_2;
	uint32_t zbox1_dram_err_status_3;
	uint32_t zbox1_dram_err_ctl;
	uint32_t zbox1_dram_err_adr;
	uint32_t zbox1_dift_timeout;
	uint32_t zbox1_dram_mapper_ctl;
	uint32_t zbox1_frc_err_adr;
	uint32_t zbox1_dift_err_status;
	uint32_t reserved2;
	uint64_t cbox_ctl;
	uint64_t cbox_stp_ctl;
	uint64_t zbox0_error_pa;
	uint64_t zbox1_error_pa;
	uint64_t zbox0_ored_syndrome;
	uint64_t zbox1_ored_syndrome;
	uint64_t reserved3[2];
};

/*
 * Data for el packet class PAL (14), type EV7_RBOX (6)
 */
struct ev7_pal_rbox_subpacket {
	uint64_t rbox_cfg;
	uint64_t rbox_n_cfg;
	uint64_t rbox_s_cfg;
	uint64_t rbox_e_cfg;
	uint64_t rbox_w_cfg;
	uint64_t rbox_n_err;
	uint64_t rbox_s_err;
	uint64_t rbox_e_err;
	uint64_t rbox_w_err;
	uint64_t rbox_io_cfg;
	uint64_t rbox_io_err;
	uint64_t rbox_l_err;
	uint64_t rbox_whoami;
	uint64_t rbox_imask;
	uint64_t rbox_intq;
	uint64_t rbox_int;
	uint64_t reserved[2];
};

/*
 * Data for el packet class PAL (14), type EV7_IO (7)
 */
struct ev7_pal_io_one_port {
	uint64_t pox_err_sum;
	uint64_t pox_tlb_err;
	uint64_t pox_spl_cmplt;
	uint64_t pox_trans_sum;
	uint64_t pox_first_err;
	uint64_t pox_mult_err;
	uint64_t pox_dm_source;
	uint64_t pox_dm_dest;
	uint64_t pox_dm_size;
	uint64_t pox_dm_ctrl;
	uint64_t reserved;
};

struct ev7_pal_io_subpacket {
	uint64_t io_asic_rev;
	uint64_t io_sys_rev;
	uint64_t io7_uph;
	uint64_t hpi_ctl;
	uint64_t crd_ctl;
	uint64_t hei_ctl;
	uint64_t po7_error_sum;
	uint64_t po7_uncrr_sym;
	uint64_t po7_crrct_sym;
	uint64_t po7_ugbge_sym;
	uint64_t po7_err_pkt0;
	uint64_t po7_err_pkt1;
	uint64_t reserved[2];
	struct ev7_pal_io_one_port ports[4];
};

/*
 * Environmental subpacket. Data used for el packets:
 * 	   class PAL (14), type AMBIENT_TEMPERATURE (10)
 * 	   class PAL (14), type AIRMOVER_FAN (11)
 * 	   class PAL (14), type VOLTAGE (12)
 * 	   class PAL (14), type INTRUSION (13)
 *	   class PAL (14), type POWER_SUPPLY (14)
 *	   class PAL (14), type LAN (15)
 *	   class PAL (14), type HOT_PLUG (16)
 */
struct ev7_pal_environmental_subpacket {
	uint16_t cabinet;
	uint16_t drawer;
	uint16_t reserved1[2];
	uint8_t module_type;
	uint8_t unit_id;		/* unit reporting condition */
	uint8_t reserved2;
	uint8_t condition;		/* condition reported       */
};

/*
 * Convert environmental type to index
 */
static inline int ev7_lf_env_index(int type)
{
	BUG_ON((type < EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE) 
	       || (type > EL_TYPE__PAL__ENV__HOT_PLUG));

	return type - EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE;
}

/*
 * Data for generic el packet class PAL.
 */
struct ev7_pal_subpacket {
	union {
		struct ev7_pal_logout_subpacket logout;	     /* Type     1 */
		struct ev7_pal_processor_subpacket ev7;	     /* Type     4 */
		struct ev7_pal_zbox_subpacket zbox;	     /* Type     5 */
		struct ev7_pal_rbox_subpacket rbox;	     /* Type     6 */
		struct ev7_pal_io_subpacket io;		     /* Type     7 */
		struct ev7_pal_environmental_subpacket env;  /* Type 10-16 */
		uint64_t as_quad[1];				     /* Raw uint64_t    */
	} by_type;
};

/*
 * Struct to contain collected logout from subpackets.
 */
struct ev7_lf_subpackets {
	struct ev7_pal_logout_subpacket *logout;		/* Type  1 */
	struct ev7_pal_processor_subpacket *ev7;		/* Type  4 */
	struct ev7_pal_zbox_subpacket *zbox;			/* Type  5 */
	struct ev7_pal_rbox_subpacket *rbox;			/* Type  6 */
	struct ev7_pal_io_subpacket *io;			/* Type  7 */
	struct ev7_pal_environmental_subpacket *env[7];	     /* Type 10-16 */

	unsigned int io_pid;
};

#endif /* __ALPHA_ERR_EV7_H */