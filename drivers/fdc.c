#include <fdc.h>
#include <video.h>
#include <stdio.h>
#include <ctype.h>
#include <io.h>

void fdc_disable_motor() {
    /* Setting bits:
     * 2: (RESET)
     * 3: (IRQ)
     */
    outportb(DOR, 0x0c);
}

void fdc_enable_motor() {
    /* Setting bits:
     * 3: (IRQ)
     * 4: (MOTA)
     */
    outportb(DOR, 0x18);
}