extern ata_irq_done

global ata_int
ata_int:
    pushad
    inc byte [ata_irq_done]
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popad
    iretd