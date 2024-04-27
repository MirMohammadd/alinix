#ifndef __ALINIX_KERNEL_COMMON_H__
#define __ALINIX_KERNEL_COMMON_H__

#include <alinix/kernel.h>
#include <alinix/pm.h>


void dev_pm_domain_set(struct device *dev, struct dev_pm_domain *pd);

#endif // __ALINIX_KERNEL_COMMON_H__