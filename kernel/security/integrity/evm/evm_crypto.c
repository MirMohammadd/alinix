/**
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

#include <alinix/kernel.h>
#include "evm.h"
#include <alinix/hash.h>
#include <alinix/crypto.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/bitops.h>
#include <alinix/list.h>

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

int evm_set_key(void *key, size_t keylen){
	int rc;

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