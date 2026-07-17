/* ***************************************************************************** */
/* *                                                                           * */
/* *                                                               ::::::::::  * */
/* *  compiler.h                                                  :+:+:+:+:+   * */
/* *                                                                 +:+       * */
/* *  By: Jack (Khalid Oumouh)                                      +#+        * */
/* *                                                               +#+         * */
/* *  Created: 2026/07/05 20:59 by Jack                    #+#    #+#          * */
/* *  Updated: 2026/07/05 20:59 by Jack                     ########           * */
/* *                                                                           * */
/* ***************************************************************************** */

#ifndef NAOIXOS_COMPILER_H
#define NAOIXOS_COMPILER_H

#if defined(__clang__)
    #define NAOIXOS_COMPILER_NAME "Clang"
#elif defined(__GNUC__)
    #define NAOIXOS_COMPILER_NAME "GCC"
#else
    #error "NaoixOS requires GCC or Clang."
#endif

#define PACKED       __attribute__((packed))
#define ALIGNED(x)   __attribute__((aligned(x)))
#define NORETURN     __attribute__((noreturn))
#define UNUSED       __attribute__((unused))

#endif
