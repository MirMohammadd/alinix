/**
 * @author Konstantin Tcholokachvili
 * @date 2013, 2014, 2017
 * @license MIT License
 *
 * Einherjar's kernel's main file
 */

#include <lib/status.h>
#include <arch/x86-pc/io/vga.h>
#include <arch/x86/mmu/gdt.h>
#include <arch/x86/interrupts/idt.h>
#include <arch/x86/interrupts/isr.h>
#include <arch/x86/interrupts/irq.h>
#include <arch/x86-pc/timer/pit.h>
#include <lib/libc.h>
#include <arch/x86-pc/bootstrap/multiboot.h>
#include <memory/physical-memory.h>
#include <threading/thread.h>
#include <threading/scheduler.h>
#include <io/console.h>
#include <colorforth/colorforth.h>



#define VGA_TEXT_BUFFER_ADDR 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ATTRIBUTE_BYTE 0x0F // White text on black background

void print_string(const char *str) {
    uint16_t *vga_buffer = (uint16_t*)VGA_TEXT_BUFFER_ADDR;
    int offset = 0;
    
    // Loop through the string and print each character
    while (*str != '\0') {
        if (*str == '\n') {
            // Move to the beginning of the next line
            offset += VGA_WIDTH - offset % VGA_WIDTH;
        } else {
            // Write the character and attribute byte to the VGA buffer
            vga_buffer[offset] = (uint16_t)(*str) | (uint16_t)(VGA_ATTRIBUTE_BYTE << 8);
            ++offset;
        }

        // Move to the next character in the string
        ++str;

        // Check if we reached the end of the screen, if so, scroll
        if (offset >= VGA_WIDTH * VGA_HEIGHT) {
            // Copy each row to the row above it
            for (int i = 0; i < VGA_HEIGHT - 1; ++i) {
                for (int j = 0; j < VGA_WIDTH; ++j) {
                    vga_buffer[i * VGA_WIDTH + j] = vga_buffer[(i + 1) * VGA_WIDTH + j];
                }
            }

            // Clear the last row
            for (int i = 0; i < VGA_WIDTH; ++i) {
                vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = (uint16_t)(' ') | (uint16_t)(VGA_ATTRIBUTE_BYTE << 8);
            }

            // Reset the offset to the beginning of the last row
            offset = (VGA_HEIGHT - 1) * VGA_WIDTH;
        }
    }
}

/**
 * The kernel entry point. All starts from here!
 */
void roentgenium_main(uint32_t magic, uint32_t address)
{
    uint16_t retval;
    multiboot_info_t *mbi;
    mbi = (multiboot_info_t *)address;

    (void)magic; // Avoid a useless warning ;-)

    // Initrd
    uint32_t initrd_start;
    uint32_t initrd_end;

    // Console
    struct console *cons = NULL;

    // GDT
    x86_gdt_setup();

    // IDT
    x86_idt_setup();

    // ISRs: Exceptions
    x86_isr_setup();

    // IRQs
    x86_irq_setup();

    // Timer: Raise IRQ0 at 100 Hz rate
    retval = x86_pit_set_frequency(100);

    assert(retval == KERNEL_OK);

    // Timer interrupt
    x86_irq_set_routine(IRQ_TIMER, timer_interrupt_handler);

    // Initrd: Initial Ram Disk
    initrd_start = *((uint32_t *)mbi->mods_addr);
    initrd_end   = *(uint32_t *)(mbi->mods_addr + 4);

    // Physical memory management
    physical_memory_setup((mbi->mem_upper<<10) + (1<<20),
		    initrd_start,
		    initrd_end);

    // Kernel threads
    threading_setup();

    // Scheduler
    scheduler_setup();

    // Enable interrupts
    asm volatile("sti");


    // Console
    console_setup(&cons, vga_display_character);


    // colorForth
    colorforth_initialize();

    struct editor_args *args = malloc(sizeof(struct editor_args));

    args->cons = cons;
    args->initrd_start = initrd_start;
    args->initrd_end = initrd_end;

    thread_create("editor", editor, args);
}
