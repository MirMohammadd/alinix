#include <alinix/types.h>


#define BEBITS	(sizeof(__be32) * 8)
/*
 * smackfs pseudo filesystem.
 */

enum smk_inos {
	SMK_ROOT_INO	= 2,
	SMK_LOAD	= 3,	/* load policy */
	SMK_CIPSO	= 4,	/* load label -> CIPSO mapping */
	SMK_DOI		= 5,	/* CIPSO DOI */
	SMK_DIRECT	= 6,	/* CIPSO level indicating direct label */
	SMK_AMBIENT	= 7,	/* internet ambient label */
	SMK_NET4ADDR	= 8,	/* single label hosts */
	SMK_ONLYCAP	= 9,	/* the only "capable" label */
	SMK_LOGGING	= 10,	/* logging */
	SMK_LOAD_SELF	= 11,	/* task specific rules */
	SMK_ACCESSES	= 12,	/* access policy */
	SMK_MAPPED	= 13,	/* CIPSO level indicating mapped label */
	SMK_LOAD2	= 14,	/* load policy with long labels */
	SMK_LOAD_SELF2	= 15,	/* load task specific rules with long labels */
	SMK_ACCESS2	= 16,	/* make an access check with long labels */
	SMK_CIPSO2	= 17,	/* load long label -> CIPSO mapping */
	SMK_REVOKE_SUBJ	= 18,	/* set rules with subject label to '-' */
	SMK_CHANGE_RULE	= 19,	/* change or add rules (long labels) */
	SMK_SYSLOG	= 20,	/* change syslog label) */
	SMK_PTRACE	= 21,	/* set ptrace rule */
#ifdef CONFIG_SECURITY_SMACK_BRINGUP
	SMK_UNCONFINED	= 22,	/* define an unconfined label */
#endif
    SMK_RELABEL_SELF = 24, /* relabel possible without CAP_MAC_ADMIN */
};


