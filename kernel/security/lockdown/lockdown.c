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

// Defining the lockdown  function here to avoid circular dependency between security.cpp
static enum lockdown_reason kernel_locked_down;


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