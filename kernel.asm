; kernel.asm
bits 16 ; 16-bit code

; Entry point
start:
    mov ah, 0x0e ; BIOS teletype function
    mov al, 'B'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'o'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'o'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 't'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'i'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'n'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'g'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, ' '  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'k'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'e'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'r'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'n'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'e'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    mov al, 'l'  ; Character to print
    int 0x10     ; Call BIOS interrupt

    jmp $        ; Infinite loop

times 510-($-$$) db 0 ; Fill the rest of the sector with zeros
dw 0xaa55             ; Boot signature
