extern ex_gpf

global gpf_handle
gpf_handle:
    pusha
    push gs
    push fs
    push es
    push ds
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call ex_gpf
    ret

extern ex_invalid_opcode

global invop_handle
invop_handle:
    pusha
    push gs
    push fs
    push es
    push ds
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call ex_invalid_opcode
    ret

extern ex_page_fault

global pf_handle
pf_handle:
    pusha
    push gs
    push fs
    push es
    push ds
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call ex_page_fault
    add esp, $4
    iretd

extern syscall_disp

global syscall_handle
syscall_handle:
    pusha
    push gs
    push fs
    push es
    push ds
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call syscall_disp
    add esp, $4
    pop gs
    pop fs
    pop es
    pop ds
    popa
    iretd