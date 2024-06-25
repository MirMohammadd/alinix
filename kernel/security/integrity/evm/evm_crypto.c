/**
 * @author Ali Mirmohammad
 * @file evm_crypto.c
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
 *  - Kernel security implement.
*/

#include <alinix/kernel.h>
#include "evm.h"
#include <alinix/hash.h>
#include <alinix/crypto.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/bitops.h>
#include <alinix/list.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel security implement")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

#define EBUSY 16
#define EINVAL 22
#define EVMKEY "evm-key"
#define MAX_KEY_SIZE 128
static unsigned char evmkey[MAX_KEY_SIZE];
static const int evmkey_len = MAX_KEY_SIZE;

static DEFINE_MUTEX(mutex);

#define EVM_SET_KEY_BUSY 0

static unsigned long evm_set_key_flags;

static const char evm_hmac[] = "hmac(sha1)";



/**
 * @brief Sets the EVM (Envelope Message) key.
 *
 * This function sets the EVM key by copying the provided key into the `evmkey`
 * buffer. It also initializes the `evm_initialized` flag to indicate that the key
 * has been set. If the key length exceeds the maximum allowed size, the function
 * returns an error. If the key cannot be set due to a busy state, the function
 * returns an error.
 *
 * @param key A pointer to the key to be set.
 * @param keylen The length of the key.
 *
 * @return If the key is set successfully, the function returns zero. Otherwise,
 *         it returns a negative error code.
 *
 * @note The function assumes that the `evmkey` buffer is large enough to hold the
 *       key.
 *
 * @example
 * void *key = ...; // Example key
 * size_t keylen = ...; // Example key length
 *
 * int rc = evm_set_key(key, keylen);
 * if (rc < 0) {
 *     // Handle error
 * }
 */
int evm_set_key(void *key, size_t keylen){
	int rc;
    static int evm_initialized;

	rc = -EBUSY;
	if (test_and_set_bit(EVM_SET_KEY_BUSY, &evm_set_key_flags))
		goto busy;
	rc = -EINVAL;
	if (keylen > MAX_KEY_SIZE)
		goto inval;
	memcpy(evmkey, key, keylen);
	evm_initialized |= EVM_INIT_HMAC;
	printk("key initialized\n");
	return 0;
inval:
    ;   // TODO : Fix here
	// clear_bit(EVM_SET_KEY_BUSY, &evm_set_key_flags);
busy:
	pr_err("key initialization failed\n");
	return rc;
}