#ifndef _KERNEL_H
#define _KERNEL_H

#include <multiboot.h>
#define asmlinkage __attribute__((regparm(0)))

extern multiboot_info_t *boot_informations;
extern char *module_start;
extern unsigned int module_end;
asmlinkage void _start(struct multiboot_info*);
int main_loop(struct multiboot_info*);

#define DREAMOS_VER "DreamOS ver 0.3 - trunk"
#define SITEURL "www.dreamos.org"

#endif