#ifndef __ALINIX_KERNEL_CRYPTO_H
#define __ALINIX_KERNEL_CRYPTO_H

#include <alinix/types.h>
#include <alinix/klist.h>

#define ARCH_KMALLOC_MINALIGN 128
#define CRYPTO_MINALIGN ARCH_KMALLOC_MINALIGN
#define CRYPTO_MINALIGN_ATTR __attribute__ ((__aligned__(CRYPTO_MINALIGN)))

struct crypto_tfm {
	refcount_t refcnt;

	u32 crt_flags;

	int node;
	
	void (*exit)(struct crypto_tfm *tfm);
	
	struct crypto_alg *__crt_alg;

	void *__crt_ctx[] CRYPTO_MINALIGN_ATTR;
};

#endif