/**
 * @author Ali Mirmohammad
 * @file evm.h
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
 *  - EVM header file implemented.
*/

#ifndef __ALINIX_KERNEL_SECURITY_EVM_H
#define __ALINIX_KERNEL_SECURITY_EVM_H


#include <alinix/kernel.h>
#include <alinix/security.h>
#include <alinix/security/integrity.h>
#include <alinix/decache.h>

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
} ;

int evm_protected_xattr(const char *req_xattr_name);

int evm_init_key(void);
int evm_update_evmxattr(struct dentry *dentry,
			const char *req_xattr_name,
			const char *req_xattr_value,
			size_t req_xattr_value_len);
int evm_calc_hmac(struct dentry *dentry, const char *req_xattr_name,
		  const char *req_xattr_value,
		  size_t req_xattr_value_len, struct evm_digest *data);
int evm_calc_hash(struct dentry *dentry, const char *req_xattr_name,
		  const char *req_xattr_value,
		  size_t req_xattr_value_len, char type,
		  struct evm_digest *data);
int evm_init_hmac(struct inode *inode, const struct xattr *xattrs,
		  char *hmac_val);
int evm_init_secfs(void);

#endif /*__ALINIX_KERNEL_SECURITY_EVM_H*/