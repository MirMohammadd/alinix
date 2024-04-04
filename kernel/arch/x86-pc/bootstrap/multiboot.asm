
extern roentgenium_main	

MBALIGN		equ	1<<0		
MEMINFO		equ	1<<1		
FLAGS		equ	MBALIGN | MEMINFO	
MAGIC		equ	0x1BADB002		
CHECKSUM	equ	-(MAGIC + FLAGS)	
STACK_SIZE	equ	0x4000		


section .multiboot

align 4

multiboot_header:
dd MAGIC
dd FLAGS
dd -(MAGIC + FLAGS)

section .text

global multiboot_entry
multiboot_entry:
	mov esp, stack + STACK_SIZE	
	mov [magic], ebx		
	mov [multiboot_info], eax	

	call roentgenium_main		

hang:
	hlt				
	jmp hang


section .bss nobits align=4
stack:          resb STACK_SIZE 
multiboot_info: resd 1          
magic:          resd 1          
