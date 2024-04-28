#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/lsm_hooks.h>

/**
 * @ref https://github.com/torvalds/linux/blob/master/security/bpf/hooks.c
*/

static struct security_hook_list bpf_lsm_hooks[] = {
    #define LSM_HOOK(RET, DEFAULT, NAME, ...)  \
    LSM_HOOK_INIT(NAME, bpf_lsm_##NAME),
    // LSM_HOOK_INIT(inode_free_security, bpf_inode_storage_free),
	// LSM_HOOK_INIT(task_free, bpf_task_storage_free),
}

