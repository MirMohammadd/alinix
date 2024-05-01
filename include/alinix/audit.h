#ifndef __ALINIX_KERNEL_AUDIT_H
#define __ALINIX_KERNEL_AUDIT_H

#include <alinix/openat2.h>
#include <alinix/types.h>
#include <alinix/time.h>
#include <alinix/list.h>
#include <alinix/sched.h>

#define AUDIT_NAMES	5

struct audit_context {
	int		    dummy;	/* must be the first element */
	enum {
		AUDIT_CTX_UNUSED,	/* audit_context is currently unused */
		AUDIT_CTX_SYSCALL,	/* in use by syscall */
		AUDIT_CTX_URING,	/* in use by io_uring */
	} context;
	enum audit_state    state, current_state;
	unsigned int	    serial;     /* serial number for record */
	int		    major;      /* syscall number */
	int		    uring_op;   /* uring operation */
	struct timespec64   ctime;      /* time of syscall entry */
	unsigned long	    argv[4];    /* syscall arguments */
	long		    return_code;/* syscall return code */
	u64		    prio;
	int		    return_valid; /* return code is valid */
	/*
	 * The names_list is the list of all audit_names collected during this
	 * syscall.  The first AUDIT_NAMES entries in the names_list will
	 * actually be from the preallocated_names array for performance
	 * reasons.  Except during allocation they should never be referenced
	 * through the preallocated_names array and should only be found/used
	 * by running the names_list.
	 */
	// struct audit_names  preallocated_names[AUDIT_NAMES];
	int		    name_count; /* total records in names_list */
	struct list_head    names_list;	/* struct audit_names->list anchor */
	char		    *filterkey;	/* key for rule that triggered record */
	// struct path	    pwd;
	// struct audit_aux_data *aux;
	// struct audit_aux_data *aux_pids;
	// struct sockaddr_storage *sockaddr;
	size_t sockaddr_len;
				/* Save things to print about task_struct */
	pid_t		    ppid;
	int	    uid, euid, suid, fsuid;
	int		    gid, egid, sgid, fsgid;
	unsigned long	    personality;
	int		    arch;

	pid_t		    target_pid;
	int	    target_auid;
	int	    target_uid;
	unsigned int	    target_sessionid;
	u32		    target_sid;
	char		    target_comm[TASK_COMM_LEN];

	struct audit_tree_refs *trees, *first_trees;
	struct list_head killed_trees;
	int tree_count;

	int type;
	union {
		struct {
			int nargs;
			long args[6];
		} socketcall;
		struct {
			int		uid;
			int			gid;
			char			mode;
			u32			osid;
			int			has_perm;
			int			perm_uid;
			unsigned int			perm_gid;
			char			perm_mode;
			unsigned long		qbytes;
		} ipc;
		struct {
			int			mqdes;
			// struct mq_attr		mqstat;
		} mq_getsetattr;
		struct {
			int			mqdes;
			int			sigev_signo;
		} mq_notify;
		struct {
			int			mqdes;
			size_t			msg_len;
			unsigned int		msg_prio;
			struct timespec64	abs_timeout;
		} mq_sendrecv;
		struct {
			int			oflag;
			char			mode;
			// struct mq_attr		attr;
		} mq_open;
		struct {
			pid_t			pid;
			// struct audit_cap_data	cap;
		} capset;
		struct {
			int			fd;
			int			flags;
		} mmap;
		struct open_how openat2;
		struct {
			int			argc;
		} execve;
		struct {
			char			*name;
		} module;
		struct {
			// struct audit_ntp_data	ntp_data;
			struct timespec64	tk_injoffset;
		} time;
	};
	int fds[2];
	// struct audit_proctitle proctitle;
};


enum audit_state {
	AUDIT_STATE_DISABLED,	/* Do not create per-task audit_context.
				 * No syscall-specific audit records can
				 * be generated. */
	AUDIT_STATE_BUILD,	/* Create the per-task audit_context,
				 * and fill it in at syscall
				 * entry time.  This makes a full
				 * syscall record available if some
				 * other part of the kernel decides it
				 * should be recorded. */
	AUDIT_STATE_RECORD	/* Create the per-task audit_context,
				 * always fill it in at syscall entry
				 * time, and always write out the audit
				 * record at syscall exit time.  */
};

#endif