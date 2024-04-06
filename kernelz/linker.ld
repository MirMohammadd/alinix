OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:x86-64)

ENTRY(_entrypoint)

SECTIONS
{
    . = 0xC0100000;

    _kernel_base = .;

    .text ALIGN(4K) : AT(ADDR(.text)-0xC0000000)
    {
        *(.multiboot)
        *(.text*)
    }

    .rodata ALIGN (4K) : AT(ADDR(.rodata)-0xC0000000)
    {
        *(.rodata)
    }

    .bss ALIGN(4K) : AT(ADDR(.bss)-0xC0000000)
    {
        *(.COMMON)
        *(.bss)
        *(.bootstrap_stack)
    }

    .data ALIGN(4K) : AT(ADDR(.data)-0xC0000000)
    {
        start_ctors = .;
        KEEP(*( .init_array ));
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
        end_ctors = .;

        *(.data*)
    }

    /DISCARD/ : {
        *(___x86.get_pc_thunk.ax)
        *(___x86.get_pc_thunk.bx)
        *(__GLOBAL_OFFSET_TABLE_)
        *(operator new*)
        *(operator delete*)
        *(HeisenOs::core::VirtualMemoryManager::virtualToPhysical*)
        *(HeisenOs::core::VirtualMemoryManager::mapVirtualToPhysical*)
        *(HeisenOs::core::pageRoundDown*)
        *(HeisenOs::core::pageRoundUp*)
        *(HeisenOs::core::Power::Reboot*)
        *(UND*)
        *(HeisenOs::core::pageRoundUp*)
        *(HeisenOs::core::pageRoundDown*)
    }

    /DISCARD/ : { *(.fini_array*) *(.comment) }

    _kernel_end = .;

    /* Link against libgcc explicitly */
    /DISCARD/ : { *(libgcc.a) }
    /DISCARD/ : { *(libgcc_s.so.1) }
    /DISCARD/ : { *(libc.a) }
}
