/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  keyboard.h                                                  :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/06 16:25 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/06 16:25 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#ifndef NAOIXOS_KEYBOARD_H
#define NAOIXOS_KEYBOARD_H
void keyboard_install(void);
int  keyboard_getchar(void); /* -1 if nothing buffered */
#endif
