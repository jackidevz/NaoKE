/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  pic.h                                                       :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/06 00:15 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/06 00:15 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#ifndef NAOIXOS_PIC_H
#define NAOIXOS_PIC_H
void pic_remap(int offset1, int offset2);
void pic_send_eoi(int irq);
void pic_unmask(int irq);
#endif
