#ifndef __ALINIX_KERNEL_CPU_MASK_H
#define __ALINIX_KERNEL_CPU_MASK_H


#define CONFIG_NR_CPUS	1

/* Places which use this should consider cpumask_var_t. */
#define NR_CPUS		CONFIG_NR_CPUS

typedef struct cpumask { char bits; } cpumask_t;


#endif