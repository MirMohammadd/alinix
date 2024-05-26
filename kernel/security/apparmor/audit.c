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

/**
 * @abstraction:
 *  - Audit implement for the kernel security.
*/


#include <alinix/kernel.h>
#include <alinix/skbuff.h>
#include <alinix/audit.h>
#include <alinix/security/apparmor/audit.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mormohammad")
MODULE_DESCRIPTION("AliNix Kernel Security Audit Module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

const char *const audit_mode_names[] = {
	"normal",
	"quiet_denied",
	"quiet",
	"noquiet",
	"all"
};

static const char *const aa_audit_type[] = {
	"AUDIT",
	"ALLOWED",
	"DENIED",
	"HINT",
	"STATUS",
	"ERROR",
	"KILLED",
	"AUTO"
};

static const char *const aa_class_names[] = {
	"none",
	"unknown",
	"file",
	"cap",
	"net",
	"rlimits",
	"domain",
	"mount",
	"unknown",
	"ptrace",
	"signal",
	"xmatch",
	"unknown",
	"unknown",
	"net",
	"unknown",
	"label",
	"posix_mqueue",
	"io_uring",
	"module",
	"lsm",
	"namespace",
	"io_uring",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"X",
	"dbus",
};



static void audit_pre(struct audit_buffer *ab, void *va){
    struct apparmor_audit_data *ad;
    if (ad->op)
        print("app armor = %s",aa_audit_type[ad->type]);
    
    if (ad->cls)
        print("Class = %s",ad->cls <= AA_CLASS_LAST? aa_class_names[ad->cls] : Unkown);
    
    if (ad->info){
		print(" info=\"%s\"", ad->info);
		if (ad->error)
			print(" error=%d", ad->error);
    }

    if (ad->name){
        print("name = %s",ad->name);

    }
}