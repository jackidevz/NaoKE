/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  serial.h                                                    :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/06 17:02 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/06 17:02 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#ifndef NAOIXOS_SERIAL_H
#define NAOIXOS_SERIAL_H
void serial_init(void);
void serial_putchar(char c);
int  serial_getchar(void);
#endif
