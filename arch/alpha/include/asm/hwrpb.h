#ifndef __ALINIX_KERNEL_ALPHA_ARCH_INCLUDE_ASM_H
#define __ALINIX_KERNEL_ALPHA_ARCH_INCLUDE_ASM_H

/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
#define INIT_HWRPB ((struct hwrpb_struct *) 0x10000000)

struct hwrpb_struct {
	unsigned long phys_addr;	/* check: physical address of the hwrpb */
	unsigned long id;		/* check: "HWRPB\0\0\0" */
	unsigned long revision;	
	unsigned long size;		/* size of hwrpb */
	unsigned long cpuid;
	unsigned long pagesize;		/* 8192, I hope */
	unsigned long pa_bits;		/* number of physical address bits */
	unsigned long max_asn;
	unsigned char ssn[16];		/* system serial number: big bother is watching */
	unsigned long sys_type;
	unsigned long sys_variation;
	unsigned long sys_revision;
	unsigned long intr_freq;	/* interval clock frequency * 4096 */
	unsigned long cycle_freq;	/* cycle counter frequency */
	unsigned long vptb;		/* Virtual Page Table Base address */
	unsigned long res1;
	unsigned long tbhb_offset;	/* Translation Buffer Hint Block */
	unsigned long nr_processors;
	unsigned long processor_size;
	unsigned long processor_offset;
	unsigned long ctb_nr;
	unsigned long ctb_size;		/* console terminal block size */
	unsigned long ctbt_offset;	/* console terminal block table offset */
	unsigned long crb_offset;	/* console callback routine block */
	unsigned long mddt_offset;	/* memory data descriptor table */
	unsigned long cdb_offset;	/* configuration data block (or NULL) */
	unsigned long frut_offset;	/* FRU table (or NULL) */
	void (*save_terminal)(unsigned long);
	unsigned long save_terminal_data;
	void (*restore_terminal)(unsigned long);
	unsigned long restore_terminal_data;
	void (*CPU_restart)(unsigned long);
	unsigned long CPU_restart_data;
	unsigned long res2;
	unsigned long res3;
	unsigned long chksum;
	unsigned long rxrdy;
	unsigned long txrdy;
	unsigned long dsr_offset;	/* "Dynamic System Recognition Data Block Table" */
};

#endif // __ALINIX_KERNEL_ALPHA_ARCH_INCLUDE_ASM_H