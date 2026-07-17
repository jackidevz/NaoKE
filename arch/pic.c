/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  pic.c                                                       :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/08 18:32 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/08 23:26 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#include <stdint.h>
#include "pic.h"
#include "io.h"

#define PIC1        0x20
#define PIC2        0xA0
#define PIC1_DATA   0x21
#define PIC2_DATA   0xA1

void pic_remap(int offset1, int offset2) {
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);

    outb(PIC1, 0x11);
    outb(PIC2, 0x11);
    outb(PIC1_DATA, (uint8_t)offset1);
    outb(PIC2_DATA, (uint8_t)offset2);
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void pic_send_eoi(int irq) {
    if (irq >= 8)
        outb(PIC2, 0x20);
    outb(PIC1, 0x20);
}

void pic_unmask(int irq) {
    uint16_t port = irq < 8 ? PIC1_DATA : PIC2_DATA;
    int bit = irq < 8 ? irq : irq - 8;
    uint8_t value = inb(port) & (uint8_t)~(1 << bit);
    outb(port, value);
}
