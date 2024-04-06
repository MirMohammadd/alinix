// #include <hardware/ata.hpp>
// #include <types.h>
// #include "arch/x86/io-ports.h"



// using namespace LIBHeisenKernel;




// uint64_t ata_identify_drive(uint8_t drive) {
//     uint16_t ata_identify_buffer[256]; // Buffer to store ATA IDENTIFY data

//     // Wait for the drive to be ready
//     while ((inb(ATA_STATUS_PORT) & 0x80) != 0x00);

//     // Select the drive and send IDENTIFY command
//     outb(ATA_DRIVE_SELECT_PORT, 0xA0 | (drive << 4));
//     outb(ATA_COMMAND_PORT, ATA_IDENTIFY_COMMAND);

//     // Wait for the drive to send data
//     while ((inb(ATA_STATUS_PORT) & 0x08) == 0x08 || (inb(ATA_STATUS_PORT) & 0x01) != 0x01);

//     // Read data from the drive
//     for (int i = 0; i < 256; i++) {
//         ata_identify_buffer[i] = inwA(ATA_DATA_PORT);
//     }

//     // Interpret ATA IDENTIFY data to get disk size
//     uint64_t sectors = ((uint64_t)ata_identify_buffer[100] << 32) |
//                        ((uint64_t)ata_identify_buffer[101] << 16) |
//                        ata_identify_buffer[60];

//     return sectors * 512; // Assuming sector size is 512 bytes
// }