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
#include <alinix/audit.h>
#include <alinix/memory.h>

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


PRIVATE __always_inline struct audit_buffer*audit_log_start(struct audit_context *ctx,gfp_t gfp_mask,int type){
    return NULL;
} 




PRIVATE inline VOID audit_ntp_init(struct audit_ntp_data *ad){
    // Write the data to the buffer
    memset(ad,0,sizeof(ad));
}

static inline void audit_ntp_set_old(struct audit_ntp_data *ad,
				     enum audit_ntp_type type, long long val)
{
	ad->vals[type].oldval = val;
}

static inline void audit_ntp_set_new(struct audit_ntp_data *ad,
				     enum audit_ntp_type type, long long val)
{
	ad->vals[type].newval = val;
}

