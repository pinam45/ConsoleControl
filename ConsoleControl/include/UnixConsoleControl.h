/*****************************************************************************************
 *                                                                                       *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2017 Maxime Pinard                                                      *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy          *
 * of this software and associated documentation files (the "Software"), to deal         *
 * in the Software without restriction, including without limitation the rights          *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell             *
 * copies of the Software, and to permit persons to whom the Software is                 *
 * furnished to do so, subject to the following conditions:                              *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all        *
 * copies or substantial portions of the Software.                                       *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR            *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,              *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE           *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,         *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE         *
 * SOFTWARE.                                                                             *
 *                                                                                       *
 *****************************************************************************************/

/**
 * @file UnixConsoleControl.h
 * @brief      Definition of Unix specific ConsoleControl related functions.
 * @details    Useful functions are provided but for a complete Unix console
 *             control see:
 *             http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html
 *             http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/termios.h.html
 *             http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/fcntl.h.html
 *             http://www.unix.org/version3/online.html
 * @author     Maxime Pinard
 *
 * @since      0.3
 */

#ifndef CONSOLECONTROL_UNIXCONSOLECONTROL_H
#define CONSOLECONTROL_UNIXCONSOLECONTROL_H


#ifdef __cplusplus
extern "C" {
#endif

#include <ConsoleControl.h>

#ifndef OS_WINDOWS

/*-------------------------------------------------------------------------*//**
 * @brief      Permanently reverse the colors. The foreground color will be used
 *             as the background color and the background color as the
 *             foreground color.
 *
 * @details    Permanent mean that after reversing the colors, setting the
 *             foreground color mean setting the background color, and setting
 *             the background color mean setting the foreground color. To go
 *             back to normal just re-reverse the colors.
 *
 * @since      0.3
 */
void cc_permanentReverseColors();

#endif //OS_WINDOWS

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_UNIXCONSOLECONTROL_H
