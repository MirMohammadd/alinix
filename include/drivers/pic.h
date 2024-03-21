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
 * @file pic.h

 */

#ifndef PIC_H
#define PIC_H

#include <types.h>

// PIC 1
#define PIC_IRQ_TIMER           0
#define PIC_IRQ_KEYBOARD        1
#define PIC_IRQ_SERIAL2         3
#define	PIC_IRQ_SERIAL1         4
#define	PIC_IRQ_PARALLEL2       5
#define	PIC_IRQ_DISKETTE        6
#define	PIC_IRQ_PARALLEL1       7
 
// PIC 2
#define	PIC_IRQ_CMOSTIMER       0
#define	PIC_IRQ_CGARETRACE      1
#define	PIC_IRQ_AUXILIARY       4
#define	PIC_IRQ_FPU             5
#define	PIC_IRQ_HDC             6


// OCW2
#define PIC_L0_MASK             1
#define PIC_L1_MASK             2
#define PIC_L2_MASK             4
#define PIC_EOI_MASK            0x20
#define PIC_SELECTION_MASK      0x40
#define PIC_ROTATE_MASK         0x80

// OCW3
#define PIC_RIS_MASK             1
#define PIC_RIR_MASK             2
#define PIC_MODE_MASK            4
#define PIC_SMM_MASK             0x20
#define PIC_ESMM_MASK            0x40
#define PIC_D7_MASK              0x80

// PIC 1 Regs
#define PIC1_REG_COMMAND        0x20
#define PIC1_REG_STATUS         0x20
#define PIC1_REG_DATA           0x21
#define PIC1_REG_IMR            0x21

// PIC 2 Regs
#define PIC2_REG_COMMAND        0xA0
#define PIC2_REG_STATUS         0xA0
#define PIC2_REG_DATA           0xA1
#define PIC2_REG_IMR            0xA1

// ICW1
#define PIC_IC4_MASK            0x1
#define PIC_SNGL_MASK           0x2
#define PIC_ADI_MASK            0x4
#define PIC_LTIM_MASK           0x8
#define PIC_INIT_MASK           0x10

// ICW1 Command Control Bits
#define PIC_IC4_EXPECT          0x1
#define PIC_IC4_NO              0x0
#define PIC_SNGL_YES            0x2
#define PIC_SNGL_NO             0x0
#define PIC_ADI_CALLINTERVAL4   0x4
#define PIC_ADI_CALLINTERVAL8   0x0
#define PIC_LTIM_LEVELTRIGGERED 0x8
#define PIC_LTIM_EDGETRIGGERED  0x0
#define PIC_INIT_YES            0x10
#define PIC_INIT_NO             0x0

// ICW4
#define PIC_UPM_MASK            0x1
#define PIC_AEOI_MASK           0x2
#define PIC_MS_MASK             0x4
#define PIC_BUF_MASK            0x8
#define PIC_SFNM_MASK           0x10

// ICW4 Command Control Bits
#define PIC_UPM_86MODE          0x1
#define PIC_UPM_MCSMODE         0x0
#define PIC_AEOI_AUTO_YES       0x2
#define PIC_AEOI_AUTO_NO        0x0
#define PIC_MS_BUFFERMASTER     0x4
#define PIC_MS_BUFFERSLAVE      0x0
#define PIC_BUF_MODE_YES        0x8
#define PIC_BUF_MODE_NO         0x0
#define PIC_SFNM_NESTEDMODE_YES 0x10
#define PIC_SFNM_NESTEDMODE_NO  0x0

void pic_send_command(uint8_t cmd, uint8_t pic);
void pic_send_data(uint8_t data, uint8_t pic);
uint8_t pic_read_data(uint8_t pic);
void pic_init(uint8_t base0, uint8_t base1);

#endif