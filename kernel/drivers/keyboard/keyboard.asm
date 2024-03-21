extern keyboard_read_key

global keyboard_int
keyboard_int:
    pushad
    push gs
    push fs
    push es
    push ds
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call keyboard_read_key
    
    mov al, 0x20
    out 0x20, al
    
    pop ds
    pop es
    pop fs
    pop gs
    popad
    iretd