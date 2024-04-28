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
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/lsm_hooks.h>
#include <alinix/panic.h>
#include <alinix/rculist.h>
#include <alinix/panic.h>

#define LSM_CONFIG_COUNT  32 /* Number of configuration options */

uint32_t lsm_active_cnt;
const struct lsm_id *lsm_idlist[LSM_CONFIG_COUNT];

void security_add_hooks(struct security_hook_list *hooks, int count,
			       const struct lsm_id *lsmid){
            
            int i;
            if (lsm_active_cnt == 0 || lsm_idlist[lsm_active_cnt - 1] != lsmid){
                if (lsm_active_cnt >= LSM_CONFIG_COUNT)
                lsm_idlist[lsm_active_cnt++] = lsmid;

            }
            for (i = 0;i < count;i++){
                hooks[i].lsmid = lsmid;
            hlist_add_tail_rcu(&hooks[i].list, hooks[i].head);
            }
        }

PRIVATE bool  lsm_allowed(struct lms_info *lsm){
    if (!IS_ENABLED(lsm)){
        return false;
    }
    return true;
}