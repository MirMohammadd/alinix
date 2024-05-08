#include <alinix/shutdown.h>
#include <alinix/init.h>
#include <alinix/kernel.h>


/**
 * @ref https://wiki.osdev.org/Shutdown
*/

void shutdown(){
    outportw(0x604, 0x2000);
    // This is mostly used in QEMU
}