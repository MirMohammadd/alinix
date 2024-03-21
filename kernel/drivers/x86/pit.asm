extern pit_ticks
extern sched_on

extern schedule

global pit_int
pit_int:

    ; push registers
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp
    push ds
    push es
    push fs
    push gs
    
    mov ebx, esp            ; save stack pointer
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    inc byte [pit_ticks]    ; increment PIT ticks
    
    mov eax, 0              ; check if scheduling is on
    cmp [sched_on], eax
    je .restore             ; scheduling off, end of interrupt
    
    push ebx
    call schedule           ; switch task
    
    mov esp, eax            ; change stack pointer

.restore:
    mov al, 0x20            ; PIC acknowledge
    out 0x20, al
    
    pop gs
    pop fs
    pop es
    pop ds
    
    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    iretd

global fork_eip
fork_eip:
    pop eax
    jmp eax