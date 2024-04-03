enter_usermode:
    ; Save RBP and RSP
    push rbp
    mov rbp, rsp

    ; Disable interrupts
    cli

    ; Load data segment descriptor (0x23 for user mode)
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Push stack segment selector (0x23 for user mode)
    push 0x23

    ; Load new stack pointer
    mov rcx, [rbp + 8]
    mov rsp, rcx

    ; Push flags onto stack
    pushfq
    pop rax

    ; OR EFLAGS from arg 3
    or rax, [rbp + 16]
    push rax

    ; Push code segment selector (0x1B for user mode)
    push 0x1B

    ; Load new instruction pointer
    mov rax, [rbp + 16]
    push rax

    ; Return to user mode
    iretq
