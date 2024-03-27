#include <heisen/typing.h>

#define IA32_TSC_DEADLINE 0x6e0

typedef struct{
    bool tsc_mode;
    bool enabled;
    bool oneshot;
    void (*handler)(int);
};

PRIVATE uint64_t tsc_read(timer_handlers_t *handlers);
int local_apic_timer_init(bool tsc_mode, void (*handler)(int), bool ap);
