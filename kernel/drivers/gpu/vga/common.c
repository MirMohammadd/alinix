#include <alinix/types.h>
#include <alinix/kernel.h>
#include <alinix/pm.h>


void dev_pm_domain_set(struct device *dev, struct dev_pm_domain *pd)
{
	if (dev->pm_domain == pd)
		return;

	WARN(pd && device_is_bound(dev),
	     "PM domains can only be changed for unbound devices\n");
	dev->pm_domain = pd;
	device_pm_check_callbacks(dev);
}