#include <8253.h>
#include <io.h>
#include <stdio.h>
#include <pic8259.h>
#include <scheduler.h>

static unsigned int ticks;
static unsigned int seconds;


void timer_pit_handler ()
{		
}

void timer_init ()
{
    int divisor = PIT_DIVISOR;

    asm ("cli");
    ticks = seconds = 0;
    outportb (PIT_COMREG,0x37);
    outportb (PIT_DATAREG0,divisor & 0xFF);
    outportb (PIT_DATAREG0,divisor >> 8);    
    asm ("sti");
}

unsigned int sleep (unsigned int secs)
{
    int p = seconds + secs;

    while (ticks != 0);
    while (seconds < p);
    return 0;
}
