#ifndef __ALINIX_KERNEL_SECURITY_COMMON_CAP_H
#define __ALINIX_KERNEL_SECURITY_COMMON_CAP_H


int cap_capable(int cap, unsigned int opts);
// int cap_ptrace_access_check(struct task_struct *child, unsigned int mode);
#endif