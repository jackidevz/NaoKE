/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  idt.c                                                       :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/07 15:03 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/07 16:08 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#include <stdint.h>
#include "idt.h"
#include "compiler.h"

struct PACKED idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t base_high;
};

struct PACKED idt_ptr {
    uint16_t limit;
    uint32_t base;
};

static struct idt_entry idt[256];
static struct idt_ptr   idtp;

extern void idt_flush(uint32_t);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector  = sel;
    idt[num].zero      = 0;
    idt[num].flags     = flags;
}

void idt_install(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    for (int i = 0; i < 256; i++)
        idt_set_gate((uint8_t)i, 0, 0, 0);

    idt_flush((uint32_t)&idtp);
}
