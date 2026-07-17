/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  isr.h                                                       :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 21:37 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/05 21:37 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */


#ifndef NAOIXOS_ISR_H
#define NAOIXOS_ISR_H
#include <stdint.h>
#include "compiler.h"

struct PACKED registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

typedef void (*irq_handler_t)(void);

void isr_install(void);
void irq_install_handler(int irq, irq_handler_t handler);
#endif
