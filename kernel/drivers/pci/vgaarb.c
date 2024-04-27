#include <alinix/kernel.h>
#include <alinix/pci.h>

struct pci_dev *vga_default;

void vga_set_default_device(struct pci_dev *pdev)
{
	if (vga_default == pdev)
		return;

	pci_dev_put(vga_default);
	vga_default = pci_dev_get(pdev);
}