/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  serial.c                                                    :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 13:29 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/05 18:01 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */


#include <stdint.h>
#include "serial.h"
#include "io.h"

#define COM1 0x3F8

static int serial_present = 0;

void serial_init(void) {
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);

    /* loopback self-test: does this port actually exist as real hardware? */
    outb(COM1 + 4, 0x1E);
    outb(COM1 + 0, 0xAE);
    serial_present = (inb(COM1 + 0) == 0xAE);

    outb(COM1 + 4, 0x0B);
}

static int transmit_empty(void) {
    return inb(COM1 + 5) & 0x20;
}

void serial_putchar(char c) {
    if (!serial_present) return;
    if (c == '\n') serial_putchar('\r');
    while (!transmit_empty()) { }
    outb(COM1, (uint8_t)c);
}

int serial_getchar(void) {
    if (!serial_present) return -1;
    if (!(inb(COM1 + 5) & 0x01)) return -1;
    return (int)(unsigned char)inb(COM1);
}
