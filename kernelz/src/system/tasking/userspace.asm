section .text

global enter_usermode

enter_usermode:
    push rbp
    mov rbp, rsp

    cli

    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push 0x23

    mov rcx, [rbp + 8]      
    mov rsp, rcx

    pushfq
    pop rax

    or rax, [rbp + 16]     
    push rax

    push 0x1B

    mov rax, [rbp + 16]     
    push rax

    iretq
