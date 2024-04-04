#ifndef _HEISEN_KERNEL_OS_HARDWARE_H
#define _HEISEN_KERNEL_OS_HARDWARE_H

struct IDEChannelRegisters {
   unsigned short base;  // I/O Base.
   unsigned short ctrl;  // Control Base
   unsigned short bmide; // Bus Master IDE
   unsigned char  nIEN;  // nIEN (No Interrupt);
} channels[2];


unsigned char ide_buf[2048] = {0};
volatile unsigned static char ide_irq_invoked = 0;
unsigned static char atapi_packet[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


struct ide_device {
   unsigned char  Reserved;    // 0 (Empty) or 1 (This Drive really exists).
   unsigned char  Channel;     // 0 (Primary Channel) or 1 (Secondary Channel).
   unsigned char  Drive;       // 0 (Master Drive) or 1 (Slave Drive).
   unsigned short Type;        // 0: ATA, 1:ATAPI.
   unsigned short Signature;   // Drive Signature
   unsigned short Capabilities;// Features.
   unsigned int   CommandSets; // Command Sets Supported.
   unsigned int   Size;        // Size in Sectors.
   unsigned char  Model[41];   // Model in string.
} ide_devices[4];




#endif // _HEISEN_KERNEL_OS_HARDWARE_H