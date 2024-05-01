#ifndef __ALINIX_KRL_SECURITY_APP_ARMOR_H
#define __ALINIX_KRL_SECURITY_APP_ARMOR_H


#include <alinix/types.h>

struct apparmor_audit_data {
    int error;
    int type;
    u16 cls;
    const char* op;
    const char *name;
	const char *info;
	u32 request;
	u32 denied;
    union {
        		/* these entries require a custom callback fn */
		struct {
			struct aa_label *peer;
			union {
				struct {
					const char *target;
					int ouid;
				} fs;
				struct {
					int rlim;
					unsigned long max;
				} rlim;
				struct {
					int signal;
					int unmappedsig;
				};
				struct {
					int type, protocol;
					// struct sock *peer_sk;
					void *addr;
					int addrlen;
				} net;
			};
		};
		struct {
			// struct aa_profile *profile;
			const char *ns;
			long pos;
		} iface;
		struct {
			const char *src_name;
			const char *type;
			const char *trans;
			const char *data;
			unsigned long flags;
		} mnt;
		struct {
			struct aa_label *target;
		} uring;
	};
};



#endif // __ALINIX_KRL_SECURITY_APP_ARMOR_H