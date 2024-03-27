#include <heisen/typing.h>
#include <heisen/stddef.h>

#define IA32_TSC_DEADLINE 0x6e0

typedef struct{
    bool tsc_mode;
    bool enabled;
    bool oneshot;
    void (*handler)(int);
}tls_apic_timer_state_t;

PRIVATE uint64_t tsc_read(timer_handlers_t *handlers);
int local_apic_timer_init(bool tsc_mode, void (*handler)(int), bool ap);
static TLS tls_apic_timer_state_t *apic_state = NULL;

PRIVATE void apic_handler(int irq){
    if (apic_state->enabled)
        if (apic_state->handler != NULL)
            apic_state->handler(irq);
        
        if (apic_state->oneshot)
            apic_state->enabled = false;
}