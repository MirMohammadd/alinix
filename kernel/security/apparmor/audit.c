#include <alinix/kernel.h>
#include <alinix/skbuff.h>


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

struct audit_buffer {
	struct sk_buff       *skb;	/* formatted skb ready to send */
	struct audit_context *ctx;	/* NULL or associated context */
	gfp_t		     gfp_mask;
};