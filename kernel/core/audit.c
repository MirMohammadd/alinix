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
 * 	- Provides security audit utility and functions.
*/

#include <alinix/kernel.h>
#include <alinix/audit.h>
#include <alinix/memory.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("AliNix Security Audit Module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


#define AUDIT_DISABLED		-1
#define AUDIT_UNINITIALIZED	0
#define AUDIT_INITIALIZED	1

enum audit_ntp_type {
	AUDIT_NTP_OFFSET,
	AUDIT_NTP_FREQ,
	AUDIT_NTP_STATUS,
	AUDIT_NTP_TAI,
	AUDIT_NTP_TICK,
	AUDIT_NTP_ADJUST,

	AUDIT_NTP_NVALS /* count */
};

struct audit_ntp_val {
	long long oldval, newval;
};

struct audit_ntp_data {
	struct audit_ntp_val vals[AUDIT_NTP_NVALS];
};


void audit_log(struct audit_context *ctx, gfp_t gfp_mask, int type,
	       const char *fmt, ...);

void audit_log(struct audit_context *ctx, gfp_t gfp_mask, int type,
	       const char *fmt, ...)
{ }

/**
 * @brief Starts an audit log by creating a new audit buffer.
 *
 * This function starts an audit log by creating a new audit buffer.
 * The audit buffer contains information about the audit log entry.
 * The function returns a pointer to the newly created audit buffer, or NULL if the audit log entry cannot be created.
 *
 * @param ctx A pointer to the audit context.
 * @param gfp_mask The memory allocation flags.
 * @param type The type of the audit log entry.
 * @return A pointer to the newly created audit buffer, or NULL if the audit log entry cannot be created.
 */
PRIVATE __always_inline struct audit_buffer*audit_log_start(struct audit_context *ctx,gfp_t gfp_mask,int type){
    return NULL;
} 



/**
 * @brief Initializes the audit NTP data structure by setting all values to 0.
 *
 * This function initializes the audit NTP data structure by setting all values to 0.
 * The audit NTP data structure contains information about NTP auditing.
 *
 * @param ad A pointer to the audit NTP data structure to be initialized.
 */
PRIVATE inline VOID audit_ntp_init(struct audit_ntp_data *ad){
    // Write the data to the buffer
    memset(ad,0,sizeof(ad));
}

/**
 * @brief Sets the old value for the specified audit NTP type in the audit NTP data structure.
 *
 * This function sets the old value for the specified audit NTP type in the audit NTP data structure.
 * The audit NTP data structure contains information about NTP auditing.
 *
 * @param ad A pointer to the audit NTP data structure.
 * @param type The audit NTP type for which to set the old value.
 * @param val The old value to set.
 */
static inline void audit_ntp_set_old(struct audit_ntp_data *ad,
				     enum audit_ntp_type type, long long val)
{
	ad->vals[type].oldval = val;
}

/**
 * @brief Sets the new value for the specified audit NTP type in the audit NTP data structure.
 *
 * This function sets the new value for the specified audit NTP type in the audit NTP data structure.
 * The audit NTP data structure contains information about NTP auditing.
 *
 * @param ad A pointer to the audit NTP data structure.
 * @param type The audit NTP type for which to set the new value.
 * @param val The new value to set.
 */
static inline void audit_ntp_set_new(struct audit_ntp_data *ad,
				     enum audit_ntp_type type, long long val)
{
	ad->vals[type].newval = val;
}

