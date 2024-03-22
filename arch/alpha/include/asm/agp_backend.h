#ifndef _ALPHA_AGP_BACKEND_H
#define _ALPHA_AGP_BACKEND_H 1

#include <types.h>

typedef	union _alpha_agp_mode {
	struct {
		uint32_t rate : 3;
		uint32_t reserved0 : 1;
		uint32_t fw : 1;
		uint32_t fourgb : 1;
		uint32_t reserved1 : 2;
		uint32_t enable : 1;
		uint32_t sba : 1;
		uint32_t reserved2 : 14;
		uint32_t rq : 8;
	} bits;
	uint32_t lw;
} alpha_agp_mode;

typedef struct _alpha_agp_info {
	struct pci_controller *hose;
	struct {
		dma_addr_t bus_base;
		unsigned long size;
		void *sysdata;
	} aperture;
	alpha_agp_mode capability;
	alpha_agp_mode mode;
	void *private;
	struct alpha_agp_ops *ops;
} alpha_agp_info;

struct alpha_agp_ops {
	int (*setup)(alpha_agp_info *);
	void (*cleanup)(alpha_agp_info *);
	int (*configure)(alpha_agp_info *);
	int (*bind)(alpha_agp_info *, off_t, struct agp_memory *);
	int (*unbind)(alpha_agp_info *, off_t, struct agp_memory *);
	unsigned long (*translate)(alpha_agp_info *, dma_addr_t);
};


#endif /* _ALPHA_AGP_BACKEND_H */