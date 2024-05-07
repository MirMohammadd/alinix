#include <alinix/kernel.h>
#include <alinix/init.h>

#include <alinix/ucapi/namespace.h>

#define PCI_ROOT_PNP_ID "PNP0A03"
#define PCI_EXPRESS_ROOT_PNP_ID "PNP0A08"


static uacpi_namespace_node *find_pci_root(uacpi_namespace_node *node){
    static const char *pci_root_ids[] = {
        PCI_ROOT_PNP_ID,
        PCI_EXPRESS_ROOT_PNP_ID,
        NULL
    };
    uacpi_namespace_node *parent = node->parent;
}