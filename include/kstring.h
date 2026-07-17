/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  kstring.h                                                   :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 21:50 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/05 21:50 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#ifndef NAOIXOS_KSTRING_H
#define NAOIXOS_KSTRING_H

#include <stddef.h>

void   *memset(void *dst, int value, size_t count);
void   *memcpy(void *dst, const void *src, size_t count);
void   *memmove(void *dst, const void *src, size_t count);
int     memcmp(const void *a, const void *b, size_t count);
size_t  strlen(const char *str);
int     strcmp(const char *a, const char *b);

#endif
