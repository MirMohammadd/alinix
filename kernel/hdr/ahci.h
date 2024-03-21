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


#ifndef __AHCI_H__
#define __AHCI_H__

#include <stdint.h>

/*Defining some macro for ports*/

#define PX_CMD_START   1
#define PX_CMD_POD 2
#define PX_CMD_SUD 4
#define PX_CMD_FRE (1<<4)
#define PX_CMD_FR (1<<14)
#define PX_CMD_CR     (1<<15)
#define PX_CMD_ATAPI  (1<<24)
#define PX_SCTL_NODETECT  0x0
#define PX_SCTL_DETECT  0x1
#define PX_SCTL_NOSPEEDLIM 0x0
#define PX_SCTL_PM_DISABLE  (0x7 << 8)
#define PX_TFD_ERR  1
#define PX_TFD_DRQ  (1<<3)
#define PX_TFD_BUSY (1<<7)

#define GHC_BOHC_OOC  (1<<3)
#define GHC_BOHC_OOS  (1<<1)
#define GHC_BOHC_SMIE  4
#define GHC_BOHC_BB    0x10
#define GHC_BOHC_BOS   1

#define GHC_CAP2_BOH   1



#define FIS_TYPE_REG_H2D  0x27
#define FIS_TYPE_REG_D2H  0x34
#define FIS_TYPE_DMA_ACT  0x39
#define FIS_TYPE_DMA_SETUP  0x41
#define FIS_TYPE_DATA  0x46
#define FIS_TYPE_BIST  0x58
#define FIS_TYPE_PIO_SETUP  0x5F
#define FIS_TYPE_DEV_BITS   0xA1


#define ATA_CMD_IDENTIFY  0xEC
#define ATA_CMD_READ_DMA  0xC8
#define ATA_CMD_READ_DMA_EXT 0x25
#define ATA_CMD_WRITE_DMA  0xCA
#define ATA_CMD_WRITE_DMA_EXT 0x35
#define ATA_CMD_PACKET   0xA0



#define FIS_REG_H2D_CTRL_INTERRUPT  (1<<7)

#define HBA_CMD_PRDT_DBC_INTERRUPT (1<<31)

#define SCTL_PORT_DET_INIT   0x1
#define SCTL_PORT_IPM_NOPART  0x100
#define SCTL_PORT_IPM_NOSLUM  0x200
#define SCTL_PORT_IPM_NODSLP  0x400
#define PX_SCTL_IPM_MASK   0xf << 8
#define PX_SCTL_IPM_ACTIVE 0x1 << 8
#define PX_SCTL_IPM_NONE  0x3 << 8

#define HBA_PX_SSTS_DET  0xfULL
#define HBA_PX_SSTS_DET_INIT  1
#define HBA_PX_SSTS_DET_PRESENT 3

#define HBA_PX_IS_TFES  (1<<30)
#define HBA_PX_CMD_ICC  (0xf << 28)
#define HBA_PX_CMD_ICC_ACTIVE  (1<<28)




#endif