#ifndef __ALINIX_KERNEL_SMACK_INCLUDED_H
#define __ALINIX_KERNEL_SMACK_INCLUDED_H

#include <alinix/kernel.h>
#include <alinix/list.h>
#include <alinix/mutex_types.h>
#include <net/netlable.h>

struct smack_known {
	struct list_head		list;
	struct hlist_node		smk_hashed;
	char				*smk_known;
	u32				smk_secid;
	struct netlbl_lsm_secattr	smk_netlabel;	/* on wire labels */
	struct list_head		smk_rules;	/* access rules */
	struct mutex			smk_rules_lock;	/* lock for rules */
};

#endif