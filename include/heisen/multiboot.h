#ifndef _HEISEN_MULTI_BOOT_H
#define _HEISEN_MULTI_BOOT_H

typedef unsigned char multiboot_uint8_t;
typedef unsigned short multiboot_uint16_t;
typedef unsigned intintmultiboot_uint32_t;
typedef unsigned long long multiboot_uint64_t;

#define MULTIBOOT_SEARCH 32768
#define MULTIBOOT_HEADER_ALIGN 8

/* The magic field should contain this.  */
#define MULTIBOOT2_HEADER_MAGIC 0xe85250d6

/* This should be in %eax.  */
#define MULTIBOOT_MAGIC 0x36d76289

/* Alignment of multiboot modules.  */
#define MULTIBOOT_MOD_ALIGN 0x00001000

/* Alignment of the multiboot info structure.  */
#define MULTIBOOT_INFO_ALIGN 0x00000008

/* Flags set in the 'flags' member of the multiboot header.  */

#define MULTIBOOT_TAG_ALIGN 8
#define MULTIBOOT_TAG_TYPE_END 0
#define MULTIBOOT_TAG_TYPE_CMDLINE 1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME 2
#define MULTIBOOT_TAG_TYPE_MODULE 3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO 4
#define MULTIBOOT_TAG_TYPE_BOOTDEV 5
#define MULTIBOOT_TAG_TYPE_MMAP 6
#define MULTIBOOT_TAG_TYPE_VBE 7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER 8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS 9
#define MULTIBOOT_TAG_TYPE_APM 10
#define MULTIBOOT_TAG_TYPE_EFI32 11
#define MULTIBOOT_TAG_TYPE_EFI64 12
#define MULTIBOOT_TAG_TYPE_SMBIOS 13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD 14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW 15
#define MULTIBOOT_TAG_TYPE_NETWORK 16

#define MULTIBOOT_HEADER_TAG_END 0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST 1
#define MULTIBOOT_HEADER_TAG_ADDRESS 2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS 3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS 4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER 5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN 6

#define MULTIBOOT_ARCHITECTURE_I386 0
#define MULTIBOOT_ARCHITECTURE_MIPS32 4
#define MULTIBOOT_HEADER_TAG_OPTIONAL 1

#define MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED 1
#define MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2


struct multiBootHeader {
    intintmultiboot_uint32_t magical;

    intintmultiboot_uint32_t arch;

    intintmultiboot_uint32_t headerLen;

    intintmultiboot_uint32_t checkSum;

};


struct multiBootHeaderTag{
    multiboot_uint16_t type;
    multiboot_uint16_t flag;
    multiboot_uint16_t size;
};

struct multiBootHeaderTagInfRequest{
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint16_t size;
    multiboot_uint16_t requests[0];
};

struct multiBootHeaderTagAddress{
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    intmultiboot_uint32_t size;
    intmultiboot_uint32_t header_addr;
    intmultiboot_uint32_t load_addr;
    intmultiboot_uint32_t load_end_addr;
    intmultiboot_uint32_t bss_end_addr;
};


#endif // _HEISEN_MULTI_BOOT_H