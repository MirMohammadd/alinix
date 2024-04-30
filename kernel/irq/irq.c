#include <alinix/irqdesc.h>
#include <alinix/types.h>

#define NR_IRQS 32
struct irq_desc irq_desc_array[NR_IRQS];


struct irq_desc *irq_to_desc(unsigned int irq){
    for (int i = 0;i < irq;i++){
        irq_desc_array->parent_irq = i;
        irq_desc_array->last_unhandled = NULL;
    }
}