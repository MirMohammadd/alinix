/**
 * @author Ali Mirmohammad
 * @file security.c
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
 *  - Security implemented here for the kernel.
*/


#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/lsm_hooks.h>
#include <alinix/panic.h>
#include <alinix/rculist.h>
#include <alinix/panic.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel Security Module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")

#define LSM_CONFIG_COUNT  32 /* Number of configuration options */

uint32_t lsm_active_cnt;
const struct lsm_id *lsm_idlist[LSM_CONFIG_COUNT];

/**
 * @brief Adds security hooks to the specified list.
 *
 * This function adds security hooks to the specified list. It takes three parameters:
 * - `hooks`: A pointer to an array of `struct security_hook_list` objects representing
 *           the security hooks to be added.
 * - `count`: The number of security hooks in the `hooks` array.
 * - `lsmid`: A pointer to a `struct lsm_id` object representing the LSM (Linux Security Module)
 *            ID associated with the security hooks.
 *
 * The function performs the following steps:
 * 1. Checks if the LSM is active. If not, or if the LSM ID is not already present in the
 *    `lsm_idlist` array, it adds the LSM ID to the `lsm_idlist` array.
 * 2. Iterates over the `hooks` array and adds each hook to the specified list by setting the
 *    `lsmid` field of each hook to the provided `lsmid` value and adding the hook to the
 *    specified list using the `hlist_add_tail_rcu` function.
 *
 * @param hooks A pointer to an array of `struct security_hook_list` objects representing
 *              the security hooks to be added.
 * @param count The number of security hooks in the `hooks` array.
 * @param lsmid A pointer to a `struct lsm_id` object representing the LSM ID associated with
 *              the security hooks.
 *
 * @note The function assumes that the `hlist_add_tail_rcu` function is available for adding
 *       hooks to the specified list.
 *
 * @example
 * struct security_hook_list hooks[3];
 * struct lsm_id lsmid = { .name = "my_lsm" };
 *
 * security_add_hooks(hooks, 3, &lsmid);
 */
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

/**
 * @brief Checks if the given LSM (Linux Security Module) is allowed.
 *
 * This function checks if the given LSM (Linux Security Module) is allowed. It takes a
 * pointer to a `struct lms_info` object representing the LSM as a parameter.
 *
 * The function performs the following steps:
 * 1. Checks if the LSM is enabled. If not, it returns `false`.
 * 2. If the LSM is enabled, it returns `true`.
 *
 * @param lsm A pointer to a `struct lms_info` object representing the LSM to check.
 *
 * @return `true` if the LSM is allowed, `false` otherwise.
 *
 * @note The function assumes that the `IS_ENABLED` macro is available for checking if the
 *       LSM is enabled.
 *
 * @example
 * struct lms_info lsm = { .name = "my_lsm" };
 *
 * bool allowed = lsm_allowed(&lsm);
 * if (allowed) {
 *     // LSM is allowed
 * } else {
 *     // LSM is not allowed
 * }
 */
PRIVATE bool  lsm_allowed(struct lms_info *lsm){
    if (!IS_ENABLED(lsm)){
        return false;
    }
    return true;
}