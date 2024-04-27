#include <alinix/kernel.h>
#include <alinix/pci.h>

void pci_dev_put(struct pci_dev *dev)
{
	if (dev)
		put_device(&dev->dev);
}