/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  vga.c                                                       :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 19:27 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/05 19:27 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#include "vga.h"
#include "kstring.h"
#include "serial.h"
#include "io.h"

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t *)0xB8000)

static size_t   term_row;
static size_t   term_col;
static uint8_t  term_color;
static uint16_t *term_buffer;

static inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg) {
    return fg | (bg << 4);
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

static void terminal_update_cursor(void) {
    uint16_t pos = (uint16_t)(term_row * VGA_WIDTH + term_col);
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void terminal_initialize(void) {
    term_row = 0;
    term_col = 0;
    term_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    term_buffer = VGA_MEMORY;

    for (size_t y = 0; y < VGA_HEIGHT; y++)
        for (size_t x = 0; x < VGA_WIDTH; x++)
            term_buffer[y * VGA_WIDTH + x] = vga_entry(' ', term_color);

    terminal_update_cursor();
}

void terminal_setcolor(uint8_t fg, uint8_t bg) {
    term_color = vga_entry_color(fg, bg);
}

static void terminal_scroll(void) {
    memmove(term_buffer, term_buffer + VGA_WIDTH,
            (VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(uint16_t));

    for (size_t x = 0; x < VGA_WIDTH; x++)
        term_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', term_color);

    term_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c) {
    serial_putchar(c);
    if (c == '\n') {
        term_col = 0;
        term_row++;
    } else if (c == '\b') {
        if (term_col > 0) {
            term_col--;
        } else if (term_row > 0) {
            term_row--;
            term_col = VGA_WIDTH - 1;
        }
        term_buffer[term_row * VGA_WIDTH + term_col] = vga_entry(' ', term_color);
    } else {
        term_buffer[term_row * VGA_WIDTH + term_col] = vga_entry((unsigned char)c, term_color);
        if (++term_col == VGA_WIDTH) {
            term_col = 0;
            term_row++;
        }
    }

    if (term_row == VGA_HEIGHT)
        terminal_scroll();

    terminal_update_cursor();
}

void terminal_write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char *data) {
    terminal_write(data, strlen(data));
}
