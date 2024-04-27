#include <alinix/types.h>
#include <alinix/device.h>
#include <alinix/klist.h>

bool device_is_bound(struct device *dev)
{
	return dev->p && klist_node_attached(&dev->p->knode_driver);
}