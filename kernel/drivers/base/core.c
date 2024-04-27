#include <alinix/kernel.h>
#include <alinix/pci.h>
#include <alinix/kobject.h>

void put_device(struct device *dev)
{
	/* might_sleep(); */
	if (dev)
		kobject_put(&dev->kobj);
}