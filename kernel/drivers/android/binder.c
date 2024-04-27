#include <alinix/types.h>
#include <alinix/kernel.h>

static HLIST_HEAD(binder_deferred_list);
static DEFINE_MUTEX(binder_deferred_lock);

static HLIST_HEAD(binder_devices);
static HLIST_HEAD(binder_procs);
static DEFINE_MUTEX(binder_procs_lock);

static HLIST_HEAD(binder_dead_nodes);
static DEFINE_SPINLOCK(binder_dead_nodes_lock);

static struct dentry *binder_debugfs_dir_entry_root;
static struct dentry *binder_debugfs_dir_entry_proc;
static atomic_t binder_last_id;

static int proc_show(struct seq_file *m, void *unused);
DEFINE_SHOW_ATTRIBUTE(proc);

#define FORBIDDEN_MMAP_FLAGS                (VM_WRITE)

enum {
	BINDER_DEBUG_USER_ERROR             = 1U << 0,
	BINDER_DEBUG_FAILED_TRANSACTION     = 1U << 1,
	BINDER_DEBUG_DEAD_TRANSACTION       = 1U << 2,
	BINDER_DEBUG_OPEN_CLOSE             = 1U << 3,
	BINDER_DEBUG_DEAD_BINDER            = 1U << 4,
	BINDER_DEBUG_DEATH_NOTIFICATION     = 1U << 5,
	BINDER_DEBUG_READ_WRITE             = 1U << 6,
	BINDER_DEBUG_USER_REFS              = 1U << 7,
	BINDER_DEBUG_THREADS                = 1U << 8,
	BINDER_DEBUG_TRANSACTION            = 1U << 9,
	BINDER_DEBUG_TRANSACTION_COMPLETE   = 1U << 10,
	BINDER_DEBUG_FREE_BUFFER            = 1U << 11,
	BINDER_DEBUG_INTERNAL_REFS          = 1U << 12,
	BINDER_DEBUG_PRIORITY_CAP           = 1U << 13,
	BINDER_DEBUG_SPINLOCKS              = 1U << 14,
};

static uint32_t binder_debug_mask = BINDER_DEBUG_USER_ERROR |
	BINDER_DEBUG_FAILED_TRANSACTION | BINDER_DEBUG_DEAD_TRANSACTION;

char* binder_devices_param = 