/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  linker.ld                                                   :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 11:47 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/10 17:37 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */



ENTRY(_start)

SECTIONS
{
    . = 1M;

    .multiboot1 : ALIGN(4) { KEEP(*(.multiboot1)) }
    .multiboot2 : ALIGN(8) { KEEP(*(.multiboot2)) }
    .text   : ALIGN(4K) { *(.text) }
    .rodata : ALIGN(4K) { *(.rodata) }
    .data   : ALIGN(4K) { *(.data) }
    .bss    : ALIGN(4K) { *(COMMON) *(.bss) }
}
