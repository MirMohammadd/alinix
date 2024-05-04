.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
    .align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.set KERNEL_VIRTUAL_BASE, 0xC0000000
.set KERNEL_PAGE_NUMBER, (KERNEL_VIRTUAL_BASE >> 22)

.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
.global stack_top
stack_top:

.section .data
.align 4
.global welcome_message
welcome_message:
    .asciz "Loading kernel...\n"

.align 0x1000
.global BootPageDirectory
BootPageDirectory:
    # identity map the first 4 MB
    .long 0x00000083
    
    # pages before kernel
    .rept (KERNEL_PAGE_NUMBER - 1)
    .long 0
    .endr
    
    # this page contains the kernel
    .long 0x00000083

    # pages after kernel
    .rept (1024 - KERNEL_PAGE_NUMBER - 1)
    .long 0
    .endr

.global _kernel_virtual_base
_kernel_virtual_base:
    .long KERNEL_VIRTUAL_BASE

.section .text
.align 4
.global _entrypoint
.type _entrypoint, @function

_entrypoint:
    # Clear the screen
    mov $0x06, %ah   # Function to scroll the screen
    xor %bh, %bh     # Blank attribute (no color)
    mov $0x00, %dl   # Number of lines to scroll
    mov $0x184F, %cx # Bottom-right corner of the screen
    mov $0x00, %dh   # Top-left corner of the screen
    int $0x10        # Call BIOS interrupt to scroll the screen

    # Print "Loading kernel" message
    lea welcome_message, %esi
    call print_string

    # Enable paging (assuming you have set up the page directory and tables)
    mov %cr3, %eax   # Load the address of the page directory into eax
    mov %eax, %cr3   # Set cr3 to the address of the page directory

    mov %cr0, %eax   # Load the value of cr0 into eax
    or $0x80000001, %eax  # Set the paging bit (bit 31) and the protection bit (bit 0)
    mov %eax, %cr0   # Write eax back to cr0 to enable paging

    # Jump to the higher-half kernel
    lea 4f, %eax     # Load the address of label 4 into eax
    jmp *%eax        # Jump to the address in eax

4:
    # Unmap the identity-mapped pages
    movl $0, BootPageDirectory
    invlpg 0

    movl $stack_top, %esp
    # Mark end of call stack for unwinding
    movl $0, %ebp

    add $KERNEL_VIRTUAL_BASE, %ebx

    call callConstructors

    push $_kernel_base
    push $_kernel_end
    push %eax
    push %ebx
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop

print_string:
    mov $0x0E, %ah   # Set function to teletype output
.loop:
    lodsb            # Load next byte of string
    test %al, %al    # Check for null terminator
    jz .done         # If null terminator, we're done
    int $0x10        # Otherwise, print character
    jmp .loop        # Repeat for next character
.done:
    ret
