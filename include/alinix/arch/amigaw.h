#ifndef __ALINIX_KERNEL_AMIGAW_H
#define __ALINIX_KERNEL_AMIGAW_H


#define PIA_REG_PADWIDTH 255



struct CIA {
    unsigned char pra;		char pad0[0xff];
    unsigned char prb;		char pad1[0xff];
    unsigned char ddra;		char pad2[0xff];
    unsigned char ddrb;		char pad3[0xff];
    unsigned char talo;		char pad4[0xff];
    unsigned char tahi;		char pad5[0xff];
    unsigned char tblo;		char pad6[0xff];
    unsigned char tbhi;		char pad7[0xff];
    unsigned char todlo;	char pad8[0xff];
    unsigned char todmid;	char pad9[0xff];
    unsigned char todhi;	char pada[0x1ff];
    unsigned char sdr;		char padb[0xff];
    unsigned char icr;		char padc[0xff];
    unsigned char cra;		char padd[0xff];
    unsigned char crb;		char pade[0xff];
};


struct pia {
	union {
		volatile unsigned char pra;
		volatile unsigned char ddra;
	} ua;
	unsigned char pad1[PIA_REG_PADWIDTH];
	volatile unsigned char cra;
	unsigned char pad2[PIA_REG_PADWIDTH];
	union {
		volatile unsigned char prb;
		volatile unsigned char ddrb;
	} ub;
	unsigned char pad3[PIA_REG_PADWIDTH];
	volatile unsigned char crb;
	unsigned char pad4[PIA_REG_PADWIDTH];
};


#define CIAA_PHYSADDR	  (0xbfe001)
#define CIAB_PHYSADDR	  (0xbfd000)
#define ciaa   ((*(volatile struct CIA *)(zTwoBase + CIAA_PHYSADDR)))
#define ciab   ((*(volatile struct CIA *)(zTwoBase + CIAB_PHYSADDR)))

#endif