[bits 16]
[org 0x7c00]

start:
    mov ax, 0x03 ; Set video mode to 80x25 16-color text mode
    int 0x10

    mov ah, 0x0B ; Set text color and background
    mov bh, 0x00 ; Page number (0)
    mov bl, 0x01 ; Text color (white)
    mov cx, 0x00 ; Number of characters to change (0 means all)
    mov dx, 0x10 ; Attribute byte (background color is 0x10 for blue)
    int 0x10

    ; Your kernel code here

    jmp $ ; Infinite loop

times 510 - ($ - $$) db 0 ; Fill the rest of the sector with zeros
dw 0xAA55 ; Boot signature
