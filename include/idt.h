/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  idt.h                                                       :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 21:12 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/05 21:12 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */



#ifndef NAOIXOS_IDT_H
#define NAOIXOS_IDT_H
#include <stdint.h>
void idt_install(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
#endif
