// #include <alinix/types.h>
// #include <smack/smack.h>



// #define BEBITS	(sizeof(__be32) * 8)
// /*
//  * smackfs pseudo filesystem.
//  */

// enum smk_inos {
// 	SMK_ROOT_INO	= 2,
// 	SMK_LOAD	= 3,	/* load policy */
// 	SMK_CIPSO	= 4,	/* load label -> CIPSO mapping */
// 	SMK_DOI		= 5,	/* CIPSO DOI */
// 	SMK_DIRECT	= 6,	/* CIPSO level indicating direct label */
// 	SMK_AMBIENT	= 7,	/* internet ambient label */
// 	SMK_NET4ADDR	= 8,	/* single label hosts */
// 	SMK_ONLYCAP	= 9,	/* the only "capable" label */
// 	SMK_LOGGING	= 10,	/* logging */
// 	SMK_LOAD_SELF	= 11,	/* task specific rules */
// 	SMK_ACCESSES	= 12,	/* access policy */
// 	SMK_MAPPED	= 13,	/* CIPSO level indicating mapped label */
// 	SMK_LOAD2	= 14,	/* load policy with long labels */
// 	SMK_LOAD_SELF2	= 15,	/* load task specific rules with long labels */
// 	SMK_ACCESS2	= 16,	/* make an access check with long labels */
// 	SMK_CIPSO2	= 17,	/* load long label -> CIPSO mapping */
// 	SMK_REVOKE_SUBJ	= 18,	/* set rules with subject label to '-' */
// 	SMK_CHANGE_RULE	= 19,	/* change or add rules (long labels) */
// 	SMK_SYSLOG	= 20,	/* change syslog label) */
// 	SMK_PTRACE	= 21,	/* set ptrace rule */
// #ifdef CONFIG_SECURITY_SMACK_BRINGUP
// 	SMK_UNCONFINED	= 22,	/* define an unconfined label */
// #endif
//     SMK_RELABEL_SELF = 24, /* relabel possible without CAP_MAC_ADMIN */
// };

// static DEFINE_MUTEX(smack_cipso_lock);
// static DEFINE_MUTEX(smack_ambient_lock);
// static DEFINE_MUTEX(smk_net4addr_lock);
// static DEFINE_MUTEX(smk_net6addr_lock);



// struct smack_known *smack_net_ambient;

// #ifdef CONFIG_SECURITY_SMACK_BRINGUP
// /*
//  * Allow one label to be unconfined. This is for
//  * debugging and application bring-up purposes only.
//  * It is bad and wrong, but everyone seems to expect
//  * to have it.
//  */
// struct smack_known *smack_unconfined;
// #endif

// /*
//  * If this value is set restrict syslog use to the label specified.
//  * It can be reset via smackfs/syslog
//  */
// struct smack_known *smack_syslog_label;

// /*
//  * Ptrace current rule
//  * SMACK_PTRACE_DEFAULT    regular smack ptrace rules (/proc based)
//  * SMACK_PTRACE_EXACT      labels must match, but can be overriden with
//  *			   CAP_SYS_PTRACE
//  * SMACK_PTRACE_DRACONIAN  labels must match, CAP_SYS_PTRACE has no effect
//  */
// int smack_ptrace_rule = SMACK_PTRACE_DEFAULT;

// /*
//  * Certain IP addresses may be designated as single label hosts.
//  * Packets are sent there unlabeled, but only from tasks that
//  * can write to the specified label.
//  */

// LIST_HEAD(smk_net4addr_list);
// #if IS_ENABLED(CONFIG_IPV6)
// LIST_HEAD(smk_net6addr_list);
// #endif /* CONFIG_IPV6 */

// /*
//  * Rule lists are maintained for each label.
//  */
// struct smack_parsed_rule {
// 	struct smack_known	*smk_subject;
// 	struct smack_known	*smk_object;
// 	int			smk_access1;
// 	int			smk_access2;
// };