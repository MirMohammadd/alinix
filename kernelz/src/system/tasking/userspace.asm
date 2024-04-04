section .text

global enter_usermode

enter_usermode:
    push ebp
    mov ebp, esp

    cli

    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push 0x23

    mov ecx, dword [ebp + 8]   
    mov esp, ecx

    pushfd
    pop eax

    or eax, dword [ebp + 12]   
    push eax

    push 0x1B

    mov eax, dword [ebp + 12]  
    push eax

    iretd
