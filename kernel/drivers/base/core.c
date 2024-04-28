#include <alinix/kernel.h>
#include <alinix/pci.h>
#include <alinix/kobject.h>


static LIST_HEAD(deferred_sync);
static unsigned int defer_sync_state_count = 1;
static DEFINE_MUTEX(fwnode_link_lock);
static bool fw_devlink_is_permissive(void);
static void __fw_devlink_link_to_consumers(struct device *dev);
static bool fw_devlink_drv_reg_done;
static bool fw_devlink_best_effort;


void put_device(struct device *dev)
{
	/* might_sleep(); */
	if (dev)
		// kobject_put(&dev->kobj);
        return; // TODO: Fix here
}