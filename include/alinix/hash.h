#ifndef __ALINIX_KERNEL_HASH_H
#define __ALINIX_KERNEL_HASH_H


#include <alinix/crypto.h>\


struct crypto_shash {
	unsigned int descsize;
	struct crypto_tfm base;
};

#endif // __ALINIX_KERNEL_HASH_H