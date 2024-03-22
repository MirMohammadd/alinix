
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
 * @file 8250.h

 */


#define FL_BASE_MASK 0x0007
#define FL_BASE0		0x0000
#define FL_BASE1		0x0001
#define FL_BASE2		0x0002
#define FL_BASE3		0x0003
#define FL_BASE4		0x0004


#define FL_BASE_BARS		0x0008

/* do not assign an irq */
#define FL_NOIRQ		0x0080


/* Use the Base address register size to cap number of ports */
#define FL_REGION_SZ_CAP	0x0100


struct pciserial_board{
    unsigned int flags;
    unsigned int num_ports;
    unsigned int base_baud;
    unsigned int uart_offset;
    unsigned int reg_shift;
    unsigned int first_offset;
};

struct serial_private;
struct serial_private *
pciserial_init_ports(struct pci_dev *dev, const struct pciserial_board *board);
void pciserial_remove_ports(struct serial_private *priv);
void pciserial_suspend_ports(struct serial_private *priv);
void pciserial_resume_ports(struct serial_private *priv);
