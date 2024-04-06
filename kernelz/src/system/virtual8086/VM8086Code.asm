[bits 16]

global VM86CodeStart
VM86CodeStart:

global Int86
Int86:
    push cs
    pop ds

    mov byte [Int86.doInt - VM86CodeStart + 1], al

    mov ax, word [0x8000]
    mov bx, word [0x8002]
    mov cx, word [0x8004]
    mov dx, word [0x8006]

    mov di, word [0x8008]

.doInt:
    int 0x0	
    		
   
    push ds
    push cs
    pop ds
    
    mov word [0x8000], ax
    mov word [0x8002], bx
    mov word [0x8004], cx
    mov word [0x8006], dx

    mov word [0x8008], di

    
    int 0xFE

global diskInfo
diskInfo:
    mov dl, al      
    mov ax, 0x4800  

    
    mov word [0x7000], 0x42
    mov si, 0x7000

    int 0x13        
    jc diskInfoError

    
    int 0xFE

diskInfoError:
    mov word [0x7000], 0 
    
    int 0xFE

global VM86CodeEnd
VM86CodeEnd:
