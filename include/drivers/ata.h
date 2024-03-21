/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file ata.h

 */
#ifndef ATA_H
#define ATA_H

#include <types.h>
/**
 * represents the I/O port address for accessing the primary data register of the ATA controller.
 * @note reads the primary errors and etc from the primary ATA hard drive
*/
#define ATA_PRIMARY_DATA            0x1F0
#define ATA_PRIMARY_ERROR           0x1F1
#define ATA_PRIMARY_SECTORS         0x1F2
/**
 * @note access lower 8 bits of LBA for the primary ATA hard drive
*/
#define ATA_PRIMARY_LBA_LOW         0x1F3

/**
 * @note This will define the upper 8 bits of LBA for the primary ATA hard drive
*/

#define ATA_PRIMARY_LBA_MID         0x1F4

/**
 * @note This will define the upper 8 bits of LBA for the primary ATA hard drive
*/

#define ATA_PRIMARY_LBA_HIGH        0x1F5

/**
 * @note other ATA macros
*/

#define ATA_PRIMARY_DRIVE_SEL       0x1F6
#define ATA_PRIMARY_STATUS          0x1F7
#define ATA_PRIMARY_IRQ             14

/**
 * @note other ATA macros (secondary)
*/

#define ATA_SECONDARY_DATA          0x170
#define ATA_SECONDARY_ERR           0x171
#define ATA_SECONDARY_SECTORS       0x172
#define ATA_SECONDARY_LBA_LOW       0x173
#define ATA_SECONDARY_LBA_MID       0x174
#define ATA_SECONDARY_LBA_HIGH      0x175
#define ATA_SECONDARY_DRIVE_SEL     0x176
#define ATA_SECONDARY_STATUS        0x177
#define ATA_SECONDARY_IRQ           15

#define ATA_IDENTIFY                0xEC


#endif // ATA_H