#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/compiler.h>
#include <alinix/lsm_hooks.h>

#define LSM_ID_BPF 109

/**
 * @ref https://github.com/torvalds/linux/blob/master/security/bpf/hooks.c
*/

static const struct lsm_id bpf_lsmid  = {
	.name = "bpf",
	.id = LSM_ID_BPF,
};

