/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  keyboard.c                                                  :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 01:26 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/15 21:31 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */



#include <stdint.h>
#include "keyboard.h"
#include "isr.h"
#include "io.h"
#include "pic.h"
#include "vga.h"

#define KBD_BUF_SIZE 256
static char kbd_buf[KBD_BUF_SIZE];
static volatile int kbd_head = 0, kbd_tail = 0;
static int shift_on = 0;
static int break_pending = 0;
static int extended_pending = 0;
static int current_set = 1;

static const char sc1_ascii[128] = {
    [0x01] = 27,
    [0x02]='1',[0x03]='2',[0x04]='3',[0x05]='4',[0x06]='5',
    [0x07]='6',[0x08]='7',[0x09]='8',[0x0A]='9',[0x0B]='0',
    [0x0C]='-',[0x0D]='=',[0x0E]='\b',[0x0F]='\t',
    [0x10]='q',[0x11]='w',[0x12]='e',[0x13]='r',[0x14]='t',
    [0x15]='y',[0x16]='u',[0x17]='i',[0x18]='o',[0x19]='p',
    [0x1A]='[',[0x1B]=']',[0x1C]='\n',
    [0x1E]='a',[0x1F]='s',[0x20]='d',[0x21]='f',[0x22]='g',
    [0x23]='h',[0x24]='j',[0x25]='k',[0x26]='l',[0x27]=';',
    [0x28]='\'',[0x29]='`',[0x2B]='\\',
    [0x2C]='z',[0x2D]='x',[0x2E]='c',[0x2F]='v',[0x30]='b',
    [0x31]='n',[0x32]='m',[0x33]=',',[0x34]='.',[0x35]='/',
    [0x37]='*',[0x39]=' ',
};
static const char sc1_ascii_shift[128] = {
    [0x01] = 27,
    [0x02]='!',[0x03]='@',[0x04]='#',[0x05]='$',[0x06]='%',
    [0x07]='^',[0x08]='&',[0x09]='*',[0x0A]='(',[0x0B]=')',
    [0x0C]='_',[0x0D]='+',[0x0E]='\b',[0x0F]='\t',
    [0x10]='Q',[0x11]='W',[0x12]='E',[0x13]='R',[0x14]='T',
    [0x15]='Y',[0x16]='U',[0x17]='I',[0x18]='O',[0x19]='P',
    [0x1A]='{',[0x1B]='}',[0x1C]='\n',
    [0x1E]='A',[0x1F]='S',[0x20]='D',[0x21]='F',[0x22]='G',
    [0x23]='H',[0x24]='J',[0x25]='K',[0x26]='L',[0x27]=':',
    [0x28]='"',[0x29]='~',[0x2B]='|',
    [0x2C]='Z',[0x2D]='X',[0x2E]='C',[0x2F]='V',[0x30]='B',
    [0x31]='N',[0x32]='M',[0x33]='<',[0x34]='>',[0x35]='?',
    [0x37]='*',[0x39]=' ',
};

static const char sc2_ascii[128] = {
    [0x16]='1',[0x1E]='2',[0x26]='3',[0x25]='4',[0x2E]='5',
    [0x36]='6',[0x3D]='7',[0x3E]='8',[0x46]='9',[0x45]='0',
    [0x4E]='-',[0x55]='=',[0x66]='\b',[0x0D]='\t',
    [0x15]='q',[0x1D]='w',[0x24]='e',[0x2D]='r',[0x2C]='t',
    [0x35]='y',[0x3C]='u',[0x43]='i',[0x44]='o',[0x4D]='p',
    [0x54]='[',[0x5B]=']',[0x5A]='\n',
    [0x1C]='a',[0x1B]='s',[0x23]='d',[0x2B]='f',[0x34]='g',
    [0x33]='h',[0x3B]='j',[0x42]='k',[0x4B]='l',[0x4C]=';',
    [0x52]='\'',[0x0E]='`',[0x5D]='\\',
    [0x1A]='z',[0x22]='x',[0x21]='c',[0x2A]='v',[0x32]='b',
    [0x31]='n',[0x3A]='m',[0x41]=',',[0x49]='.',[0x4A]='/',
    [0x29]=' ',
};
static const char sc2_ascii_shift[128] = {
    [0x16]='!',[0x1E]='@',[0x26]='#',[0x25]='$',[0x2E]='%',
    [0x36]='^',[0x3D]='&',[0x3E]='*',[0x46]='(',[0x45]=')',
    [0x4E]='_',[0x55]='+',[0x66]='\b',[0x0D]='\t',
    [0x15]='Q',[0x1D]='W',[0x24]='E',[0x2D]='R',[0x2C]='T',
    [0x35]='Y',[0x3C]='U',[0x43]='I',[0x44]='O',[0x4D]='P',
    [0x54]='{',[0x5B]='}',[0x5A]='\n',
    [0x1C]='A',[0x1B]='S',[0x23]='D',[0x2B]='F',[0x34]='G',
    [0x33]='H',[0x3B]='J',[0x42]='K',[0x4B]='L',[0x4C]=':',
    [0x52]='"',[0x0E]='~',[0x5D]='|',
    [0x1A]='Z',[0x22]='X',[0x21]='C',[0x2A]='V',[0x32]='B',
    [0x31]='N',[0x3A]='M',[0x41]='<',[0x49]='>',[0x4A]='?',
    [0x29]=' ',
};

static void kbd_push(char c) {
    int next = (kbd_head + 1) % KBD_BUF_SIZE;
    if (next != kbd_tail) {
        kbd_buf[kbd_head] = c;
        kbd_head = next;
    }
}

static void keyboard_irq(void) {
    uint8_t sc = inb(0x60);

    if (sc == 0xE0) { extended_pending = 1; return; }
    if (extended_pending) { extended_pending = 0; return; }

    if (sc == 0xF0) {
        current_set = 2;
        break_pending = 1;
        return;
    }

    if (current_set == 1 || (sc & 0x80)) {
        current_set = 1;
        if (sc & 0x80) {
            uint8_t make = sc & 0x7F;
            if (make == 0x2A || make == 0x36) shift_on = 0;
            return;
        }
        if (sc == 0x2A || sc == 0x36) { shift_on = 1; return; }
        char c = shift_on ? sc1_ascii_shift[sc] : sc1_ascii[sc];
        if (c) kbd_push(c);
        return;
    }

    if (break_pending) {
        break_pending = 0;
        if (sc == 0x12 || sc == 0x59) shift_on = 0;
        return;
    }
    if (sc == 0x12 || sc == 0x59) { shift_on = 1; return; }
    char c = shift_on ? sc2_ascii_shift[sc] : sc2_ascii[sc];
    if (c) kbd_push(c);
}

void keyboard_install(void) {
    irq_install_handler(1, keyboard_irq);
    pic_unmask(1);
}

int keyboard_getchar(void) {
    if (kbd_head == kbd_tail) return -1;
    char c = kbd_buf[kbd_tail];
    kbd_tail = (kbd_tail + 1) % KBD_BUF_SIZE;
    return (int)(unsigned char)c;
}
