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




#endif // ATA_H