#ifndef __ALINIX_KERNEL_NET_LABEL_NET_H
#define __ALINIX_KERNEL_NET_LABEL_NET_H


#include <alinix/kernel.h>

struct netlbl_lsm_secattr {
	u32 flags;
	/* bitmap values for 'flags' */
#define NETLBL_SECATTR_NONE             0x00000000
#define NETLBL_SECATTR_DOMAIN           0x00000001
#define NETLBL_SECATTR_DOMAIN_CPY       (NETLBL_SECATTR_DOMAIN | \
					 NETLBL_SECATTR_FREE_DOMAIN)
#define NETLBL_SECATTR_CACHE            0x00000002
#define NETLBL_SECATTR_MLS_LVL          0x00000004
#define NETLBL_SECATTR_MLS_CAT          0x00000008
#define NETLBL_SECATTR_SECID            0x00000010
	/* bitmap meta-values for 'flags' */
#define NETLBL_SECATTR_FREE_DOMAIN      0x01000000
#define NETLBL_SECATTR_CACHEABLE        (NETLBL_SECATTR_MLS_LVL | \
					 NETLBL_SECATTR_MLS_CAT | \
					 NETLBL_SECATTR_SECID)
	u32 type;
	char *domain;
	struct netlbl_lsm_cache *cache;
	struct {
		struct {
			struct netlbl_lsm_catmap *cat;
			u32 lvl;
		} mls;
		u32 secid;
	} attr;
};

#endif