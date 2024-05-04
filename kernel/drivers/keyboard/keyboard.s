section .text
    global _start

_start:
    ; Set up stack pointer
    mov ax, 0x07C0
    add ax, 288
    mov ss, ax
    mov sp, 4096
    
    ; Set up data segment
    mov ax, 0x07C0
    mov ds, ax
    
    ; Call the initialization routine
    call clear_screen
    
    ; Initialize the keyboard
    call init_keyboard
    
    ; Main loop
    .loop:
        ; Wait for a key press
        call wait_for_key_press
        
        ; Read the scancode
        call read_scan_code
        
        ; Print the scancode
        call print_scan_code
        
        ; Repeat
        jmp .loop

clear_screen:
    ; Clear the screen
    mov ah, 0x06
    mov al, 0x00
    mov bh, 0x07
    mov cx, 0x0000
    mov dx, 0x184F
    int 0x10
    ret
    
init_keyboard:
    ; Initialize the keyboard
    mov ah, 0
    int 0x16
    ret
    
wait_for_key_press:
    ; Wait for a key press
    xor ah, ah
    int 0x16
    ret
    
read_scan_code:
    ; Read the scan code
    mov ah, 0
    int 0x16
    ret
    
print_scan_code:
    ; Print the scan code
    mov ah, 0x0E
    mov bh, 0
    mov bl, 0x07
    int 0x10
    ret
