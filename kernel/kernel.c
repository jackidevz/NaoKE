/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  kernel.c                                                    :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/06 21:18 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/13 18:53 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */



#include <stdint.h>
#include "vga.h"
#include "naoixsh.h"
#include "compiler.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "keyboard.h"
#include "serial.h"
#include "version.h"

#define LEGACY_BIOS_BOOT_MAGIC       0xB105F00D
#define MULTIBOOT1_BOOTLOADER_MAGIC  0x2BADB002
#define MULTIBOOT2_BOOTLOADER_MAGIC  0x36D76289

void kmain(uint32_t magic, uint32_t info_addr) {
    (void)info_addr;

    serial_init();
    terminal_initialize();
    terminal_setcolor(VGA_LIGHT_GREEN, VGA_BLACK);
    terminal_writestring("NaoixOS "KEVER"\n");
    terminal_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
    terminal_writestring("Compiled with: " NAOIXOS_COMPILER_NAME "\n");

    if (magic == MULTIBOOT2_BOOTLOADER_MAGIC) {
        terminal_writestring("Boot: Multiboot2\n");
    } else if (magic == MULTIBOOT1_BOOTLOADER_MAGIC) {
        terminal_writestring("Boot: Multiboot v1 (direct QEMU -kernel)\n");
    } else if (magic == LEGACY_BIOS_BOOT_MAGIC) {
        terminal_writestring("Boot: custom BIOS bootloader (Limbo/SeaBIOS)\n");
    } else {
        terminal_setcolor(VGA_LIGHT_RED, VGA_BLACK);
        terminal_writestring("Warning: unrecognized boot magic.\n");
        terminal_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
    }

    gdt_install();
    idt_install();
    isr_install();
    keyboard_install();
    __asm__ volatile ("sti");

    terminal_writestring("\n");
    naoixsh_init();
    naoixsh_run();

    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}
