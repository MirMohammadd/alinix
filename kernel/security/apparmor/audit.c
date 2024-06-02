/**
 * @author Ali Mirmohammad
 * @file audit.c
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



/**
 * @brief Prints audit information to the console.
 *
 * This function prints audit information to the console based on the provided
 * `audit_buffer` and `apparmor_audit_data` structures. It checks if the audit
 * operation (`ad->op`) is present and prints the audit type using the `aa_audit_type`
 * array. It also checks if the audit class (`ad->cls`) is present and prints the
 * corresponding class name using the `aa_class_names` array. If the audit information
 * (`ad->info`) is present, it prints the information along with the error code
 * (`ad->error`) if it is also present. Finally, if the audit name (`ad->name`) is
 * present, it prints the name.
 *
 * @param ab A pointer to the `audit_buffer` structure.
 * @param va A pointer to the `apparmor_audit_data` structure.
 *
 * @return This function does not return a value.
 *
 * @note The function assumes that the `audit_buffer` and `apparmor_audit_data` structures
 *       are valid.
 *
 * @example
 * struct audit_buffer *ab = ...; // Example audit_buffer
 * struct apparmor_audit_data *ad = ...; // Example apparmor_audit_data
 *
 * audit_pre(ab, ad);
 */
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