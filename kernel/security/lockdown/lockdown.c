/**
 * @author Ali Mirmohammad
 * @file lockdown.c
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
 *  - Lock down , kernel security implementation.
*/
#include <alinix/security.h>
#include <alinix/uapi/asm-generic/errorno-base.h>
#include <alinix/kernel.h>
#include <alinix/string.h>
#include <alinix/lsm_hooks.h>
#include <alinix/types.h>
#include <alinix/stdio.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>
#include <alinix/module.h>


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("AliNix Security Module for lock down.")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")



// Defining the lockdown  function here to avoid circular dependency between security.cpp
static enum lockdown_reason kernel_locked_down;
static const char* lockdown_reasons;

static const enum lockdown_reason lockdown_levels[] = {LOCKDOWN_NONE,
						 LOCKDOWN_INTEGRITY_MAX,
						 LOCKDOWN_CONFIDENTIALITY_MAX};


/*
 * Put the kernel into lock-down mode.
 */

/**
 * @brief Locks the kernel down to a specified level.
 *
 * This function locks the kernel down to a specified level. It checks if the current
 * kernel lockdown level is greater than or equal to the requested lockdown level.
 * If it is, the function returns an error with the code `-EPERM`. Otherwise, it prints
 * a notice indicating that the kernel is locked down and provides a link to the
 * `kernel_lockdown.7` manual page. The function then returns zero to indicate success.
 *
 * @param where A pointer to a string indicating the location where the lockdown is being
 *              requested.
 * @param level An enum value representing the lockdown level to be set.
 *
 * @return If the kernel is successfully locked down, the function returns zero.
 *         Otherwise, it returns an error code with the value `-EPERM`.
 *
 * @note The function assumes that the `pr_notice` function is available for printing
 *       the notice message.
 *
 * @example
 * const char* where = "module initialization";
 * enum lockdown_reason level = LOCKDOWN_REASON_MODULE_INIT;
 *
 * int rc = lock_kernel_down(where, level);
 * if (rc < 0) {
 *     // Handle error
 * }
 */
static int lock_kernel_down(const char* where,enum lockdown_reason level){
    if (kernel_locked_down >= level){
        return -EPERM;
    }
    pr_notice("Kernel is locked down from %s; see man kernel_lockdown.7\n",
		  where);
	return 0;
}


/**
 * @brief Locks the kernel down based on the provided lockdown level.
 *
 * This function locks the kernel down based on the provided lockdown level. It checks
 * if the `level` parameter is NULL and returns an error with the code `-EINVAL` if it
 * is. If the `level` parameter is not NULL, it compares it with the strings "integrity"
 * and "confidentiality". If it matches "integrity", it calls the `lock_kernel_down`
 * function with the lockdown level `LOCKDOWN_INTEGRITY_MAX`. If it matches "confidentiality",
 * it calls the `lock_kernel_down` function with the lockdown level `LOCKDOWN_CONFIDENTIALITY_MAX`.
 * If it does not match either string, the function returns an error with the code `-EINVAL`.
 *
 * @param level A pointer to a string representing the lockdown level to be set.
 *
 * @return If the kernel is successfully locked down, the function returns zero.
 *         Otherwise, it returns an error code with the value `-EINVAL`.
 *
 * @note The function assumes that the `lock_kernel_down` function is available for
 *       locking down the kernel.
 *
 * @example
 * char* level = "integrity";
 *
 * int rc = lockdown_param(level);
 * if (rc < 0) {
 *     // Handle error
 * }
 */
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

/**
 * @brief Checks if the kernel is locked down for a specific reason.
 *
 * This function checks if the kernel is locked down for a specific reason. It takes
 * an enum value representing the lockdown reason as a parameter. If the provided
 * reason is greater than or equal to `LOCKDOWN_CONFIDENTIALITY_MAX`, the function
 * returns an error with the code `-EPERM`. Otherwise, it checks if the current kernel
 * lockdown level is greater than or equal to the provided reason. If it is, the function
 * checks if there is a lockdown reason associated with the provided reason. If there is,
 * it prints a message indicating that the lockdown reason is restricted and provides
 * a link to the `kernel_lockdown.7` manual page. The function then returns an error with
 * the code `-EPERM`. If the kernel is not locked down for the provided reason, the function
 * returns zero.
 *
 * @param what An enum value representing the lockdown reason to be checked.
 *
 * @return If the kernel is locked down for the provided reason, the function returns an
 *         error code with the value `-EPERM`. Otherwise, it returns zero.
 *
 * @note The function assumes that the `print` function is available for printing the
 *       lockdown message.
 *
 * @example
 * enum lockdown_reason what = LOCKDOWN_INTEGRITY_MAX;
 *
 * int rc = lockdown_is_locked_down(what);
 * if (rc < 0) {
 *     // Handle error
 * }
 */
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


/**
 * @brief Reads the lockdown levels from the file and returns them as a string.
 *
 * This function reads the lockdown levels from the file and returns them as a string.
 * It iterates over the `lockdown_levels` array and checks if there is a lockdown
 * reason associated with each level. If there is, it retrieves the label for the
 * lockdown reason and formats it into a string. If the kernel is locked down at the
 * current level, it encloses the label in square brackets. The formatted string is
 * stored in the `temp` buffer. Finally, the function returns the `temp` buffer as the
 * result of the function.
 *
 * @param filp A pointer to the file structure.
 * @param buf A pointer to the buffer where the result will be stored.
 * @param count The maximum number of characters to be read.
 * @param ppos A pointer to the file position.
 *
 * @return The number of characters read.
 *
 * @note The function assumes that the `printf` function is available for formatting
 *       the lockdown levels.
 *
 * @example
 * FILE* filp = fopen("lockdown", "r");
 * char buf[80];
 * size_t count = sizeof(buf);
 * loff_t ppos = 0;
 *
 * ssize_t rc = lockdown_read(filp, buf, count, &ppos);
 * if (rc > 0) {
 *     // Handle the result
 * }
 * fclose(filp);
 */
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

/**
 * @brief Writes the lockdown level to the file and locks the kernel down accordingly.
 *
 * This function writes the lockdown level to the file and locks the kernel down
 * accordingly. It takes a buffer containing the lockdown level as input. It
 * copies the buffer to a new string, removes the newline character if present,
 * and compares it with the labels of the lockdown levels. If a match is found,
 * it calls the `lock_kernel_down` function to lock the kernel down at the
 * corresponding lockdown level. The function returns the number of characters
 * written if successful, or an error code if the lockdown level is invalid or
 * if an error occurs during the lockdown process.
 *
 * @param file A pointer to the file structure.
 * @param buf A pointer to the buffer containing the lockdown level.
 * @param n The number of characters to be written.
 * @param ppos A pointer to the file position.
 *
 * @return The number of characters written if successful, or an error code.
 *
 * @note The function assumes that the `strcpy`, `strlen`, `strcmp`, and `free`
 *       functions are available for string manipulation.
 *
 * @example
 * struct file* file = fopen("lockdown", "w");
 * char buf[] = "integrity\n";
 * size_t n = strlen(buf);
 * loff_t ppos = 0;
 *
 * ssize_t rc = lockdown_write(file, buf, n, &ppos);
 * if (rc < 0) {
 *     // Handle error
 * }
 * fclose(file);
 */
static ssize_t lockdown_write(struct file *file, const char  *buf,
			      size_t n, loff_t *ppos)
{
	char *state;
	int i, len, err = -EINVAL;

	state = strcpy(buf, n);
	if (!state)
		return state;

	len = strlen(state);
	if (len && state[len-1] == '\n') {
		state[len-1] = '\0';
		len--;
	}

	for (i = 0; i < sizeof(lockdown_levels)/ sizeof(lockdown_levels)[0]; i++) {
		enum lockdown_reason level = lockdown_levels[i];
		const char *label = lockdown_reasons[level];

		if (label && !strcmp(state, label))
			err = lock_kernel_down("securityfs", level);
	}

	free(state);
	return err ? err : n;
}

/////////////////////////////////////

/**
 * @brief Locks the kernel down for memory corruption.
 *
 * This function locks the kernel down for memory corruption. It calls the
 * `lock_kernel_down` function to lock the kernel down at the memory corruption
 * lockdown level. The function takes a string "Kernel configuration" as the
 * reason for locking down the kernel.
 *
 * @note The function assumes that the `lock_kernel_down` function is available
 *       for locking down the kernel.
 *
 * @example
 * kernelMemoryCorruptionLockDown();
 */
void kernelMemoryCorruptionLockDown(){
    lock_kernel_down("Kernel configuration",MEMORY_CORRUPTION);
}