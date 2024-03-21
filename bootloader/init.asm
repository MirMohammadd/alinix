
global loader
extern kmain

MODULEALIGN equ 1<<0
MEMINFO     equ 1<<1
VIDMOD      equ 1<<2
FLAGS       equ MODULEALIGN | MEMINFO | VIDMOD
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .mbheader
align 4

multiboot_header:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd multiboot_header
    dd loader
    dd stack
    dd stack
    dd loader
    dd 0
    dd 1024
    dd 768
    dd 32

section .text

STACKSIZE   equ 0x4000

loader:
    mov esp, stack + STACKSIZE
    push ebx                    ; pointer to multiboot structure
    call kmain
    cli
    hlt

.hang:
    jmp .hang
    
section .bss
align 4

stack:
    resb STACKSIZE
