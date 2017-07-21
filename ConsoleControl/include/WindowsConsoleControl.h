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
 * @file WindowsConsoleControl.h
 * @brief      Definition of Windows specific ConsoleControl related functions.
 * @details    Useful functions are provided but for a complete Windows console
 *             control see:
 *             https://msdn.microsoft.com/en-us/library/windows/desktop/ms682087.aspx
 * @author     Maxime Pinard
 *
 * @since      0.3
 */

#ifndef CONSOLECONTROL_WINDOWSCONSOLECONTROL_HPP
#define CONSOLECONTROL_WINDOWSCONSOLECONTROL_HPP


#ifdef __cplusplus
extern "C" {
#endif

#include <ConsoleControl.h>

#ifdef OS_WINDOWS

/*-------------------------------------------------------------------------*//**
 * @brief      Get the cursor position in the console window.
 *
 * @return     The cursor position
 *
 * @since      0.3
 */
cc_Vector2 cc_getCursorPosition();

/*-------------------------------------------------------------------------*//**
 * @brief      Get the cursor global position.
 *
 * @details    Global mean not only the part visible in the window but the
 *             complete buffer.
 *
 * @return     The cursor global position
 *
 * @since      0.3
 */
cc_Vector2 cc_getCursorGlobalPosition();

/*-------------------------------------------------------------------------*//**
 * @brief      Reverse the colors. Current Foreground color will be used as the
 *             background color and current background color as the foreground
 *             color.
 *
 * @since      0.3
 */
void cc_reverseColors();

/*-------------------------------------------------------------------------*//**
 * @brief      Get the global console width.
 *
 * @details    Global mean not only the part visible in the window but the
 *             complete buffer.
 *
 * @return     The global console width
 *
 * @since      0.3
 */
cc_type cc_getGlobalWidth();

/*-------------------------------------------------------------------------*//**
 * @brief      Get the global console height.
 *
 * @details    Global mean not only the part visible in the window but the
 *             complete buffer.
 *
 * @return     The global console height
 *
 * @since      0.3
 */
cc_type cc_getGlobalHeight();

/*-------------------------------------------------------------------------*//**
 * @brief      Set the cursor global position.
 *
 * @details    Global mean not only the part visible in the window but the
 *             complete buffer.
 *
 * @param[in]  position  The position
 *
 * @since      0.3
 */
void cc_setCursorGlobalPosition(cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the position in the global console.
 *
 * @details    Global mean not only the part visible in the window but the
 *             complete buffer.
 *
 * @param[in]  position  The position
 *
 * @return     The position clamped down in the global console
 *
 * @since      0.3
 */
cc_Vector2 cc_globalClamp(cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Determine if the global console contains the position.
 *
 * @details    Global mean not only the part visible in the window but the
 *             complete buffer.
 *
 * @param[in]  position  The position
 *
 * @return     True if the global console contains the position, false otherwise
 *
 * @since      0.3
 */
bool cc_globalContains(cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the cursor size.
 *
 * @details    The size is the percentage of the character cell that is filled
 *             by the cursor. This value is between 1 and 100. The cursor
 *             appearance varies, ranging from completely filling the cell to
 *             showing up as a horizontal line at the bottom of the cell.
 *             (https://msdn.microsoft.com/en-us/library/windows/desktop/ms682068(v=vs.85).aspx)
 *
 * @param[in]  size  The size between 1 and 100
 */
void cc_setCursorSize(unsigned int size); /* 0-100 */ //TODO

#endif //OS_WINDOWS

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_WINDOWSCONSOLECONTROL_HPP
