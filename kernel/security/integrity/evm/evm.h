#ifndef __ALINIX_KERNEL_SECURITY_EVM_H
#define __ALINIX_KERNEL_SECURITY_EVM_H


#include <alinix/kernel.h>
#include <alinix/security.h>
#include <alinix/security/integrity.h>

#define EVM_INIT_HMAC	0x0001
#define EVM_INIT_X509	0x0002
#define EVM_ALLOW_METADATA_WRITES	0x0004
#define EVM_SETUP_COMPLETE 0x80000000 /* userland has signaled key load */

#define EVM_KEY_MASK (EVM_INIT_HMAC | EVM_INIT_X509)
#define EVM_INIT_MASK (EVM_INIT_HMAC | EVM_INIT_X509 | EVM_SETUP_COMPLETE | \
		       EVM_ALLOW_METADATA_WRITES)


struct xattr_list {
	struct list_head list;
	char *name;
	bool enabled;
};


#define EVM_NEW_FILE			0x00000001
#define EVM_IMMUTABLE_DIGSIG		0x00000002

/* EVM integrity metadata associated with an inode */
struct evm_iint_cache {
	unsigned long flags;
};

extern struct lsm_blob_sizes evm_blob_sizes;

extern int evm_initialized;

#define EVM_ATTR_FSUUID		0x0001

extern int evm_hmac_attrs;

/* List of EVM protected security xattrs */
extern struct list_head evm_config_xattrnames;

struct evm_digest {
	struct ima_digest_data hdr;
	char digest[IMA_MAX_DIGEST_SIZE];
} __packed;


#endif