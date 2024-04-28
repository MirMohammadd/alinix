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
#include <alinix/security.h>
#include <alinix/uapi/asm-generic/errorno-base.h>
#include <alinix/kernel.h>
#include <alinix/string.h>
#include <alinix/lsm_hooks.h>
#include <alinix/types.h>
#include <alinix/stdio.h>


// Defining the lockdown  function here to avoid circular dependency between security.cpp
static enum lockdown_reason kernel_locked_down;
static enum lockdown_reason *lockdown_reasons;

static const enum lockdown_reason lockdown_levels[] = {LOCKDOWN_NONE,
						 LOCKDOWN_INTEGRITY_MAX,
						 LOCKDOWN_CONFIDENTIALITY_MAX};


/*
 * Put the kernel into lock-down mode.
 */

static int lock_kernel_down(const char* where,enum lockdown_reason level){
    if (kernel_locked_down >= level){
        return -EPERM;
    }
    pr_notice("Kernel is locked down from %s; see man kernel_lockdown.7\n",
		  where);
	return 0;
}


static int __init lockdown_param(char *level){
    if (!level){
        return -EINVAL;
    }
    if (strcmp(level,"integrity"))
        /*integrity refers to the protection of data from unauthorized modification, deletion, or disclosure. */
        lock_kernel_down("command line", LOCKDOWN_INTEGRITY_MAX);
    
    /*n the other hand, refers to the protection of sensitive information from unauthorized Access*/
    else if (strcmp(level, "confidentiality"))
		lock_kernel_down("command line", LOCKDOWN_CONFIDENTIALITY_MAX);
    
    else 
        return -EINVAL;
    
    return 0;
}

static int lockdown_is_locked_down(enum lockdown_reason what){
	if (what >= LOCKDOWN_CONFIDENTIALITY_MAX,
		 "Invalid lockdown reason")
		return -EPERM;
    if (kernel_locked_down >= what) {
    if (lockdown_reasons[what])
			print("Lockdown: %s: %s is restricted; see man kernel_lockdown.7\n",
				  "Lock", lockdown_reasons[what]);
		return -EPERM;
}
    return 0;   
}

const struct lsm_id lockdown_lsmid = {
    .name = "LockDown",
    .id = LSM_ID_LOCKDOWN,
};

static int __init lockdown_lsm_init(void){

#if defined(CONFIG_LOCK_DOWN_KERNEL_FORCE_INTEGRITY)
	lock_kernel_down("Kernel configuration", LOCKDOWN_INTEGRITY_MAX);
#elif defined(CONFIG_LOCK_DOWN_KERNEL_FORCE_CONFIDENTIALITY)
	lock_kernel_down("Kernel configuration", LOCKDOWN_CONFIDENTIALITY_MAX);
#endif
}


static ssize_t lockdown_read(FILE *filp, char  *buf, size_t count,
			     loff_t *ppos){

        char temp[80];
        int i, offset = 0;
        for (i = 0; i < sizeof(lockdown_levels) / sizeof(lockdown_levels)[0]; i++){
            enum lockdown_reason level = lockdown_levels[i];

            if (lockdown_reasons[level]){
                const char* label = lockdown_reasons[level];

                if (kernel_locked_down == level)
                    offset += printf(temp+offset, "[%s] ", label);
                else
                    offset += printf(temp+offset, "%s ", label);
            }
        }

        if (offset > 0){
            temp[offset-1] = '\n';
        }

        return temp; // TODO : FIX HERE
}

static ssize_t lockdown_write(struct file *file, const char  *buf,
			      size_t n, loff_t *ppos)
{
	char *state;
	int i, len, err = -EINVAL;

	state = memdup_user_nul(buf, n);
	if (IS_ERR(state))
		return PTR_ERR(state);

	len = strlen(state);
	if (len && state[len-1] == '\n') {
		state[len-1] = '\0';
		len--;
	}

	for (i = 0; i < ARRAY_SIZE(lockdown_levels); i++) {
		enum lockdown_reason level = lockdown_levels[i];
		const char *label = lockdown_reasons[level];

		if (label && !strcmp(state, label))
			err = lock_kernel_down("securityfs", level);
	}

	free(state);
	return err ? err : n;
}