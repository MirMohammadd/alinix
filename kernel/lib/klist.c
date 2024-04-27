#include <alinix/klist.h>
#include <alinix/kernel.h>

int klist_node_attached(struct klist_node *n)
{
	return (n->n_klist != NULL);
}