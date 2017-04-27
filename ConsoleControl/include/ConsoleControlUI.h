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
 * @file ConsoleControlUI.h
 * @brief      Definition of ConsoleControl UI related functions.
 * @author     Maxime Pinard
 *
 * @since      0.1
 */

#ifndef CONSOLECONTROL_CONSOLECONTROLUI_H
#define CONSOLECONTROL_CONSOLECONTROLUI_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include <log.h>
#include <ConsoleControl.h>
#include <ConsoleControlUtility.h>
#include <ConsoleControlMenu.h>
#include <ConsoleControlInput.h>

/*-------------------------------------------------------------------------*//**
 * @brief      Display the menu with the table style ('-' for horizontal lines,
 *             '|' for vertical lines, '+' for angles and intersections).
 *
 * @details    Allow the user to see and select a choice from the menu using the
 *             control keys, the user choice is the @c currentChoice field of
 *             the menu struct. This is a blocking function, return when the
 *             user press enter (or escape if the @c choiceOnEscape field of the
 *             menu struct is a valid choice).
 *
 *             Note: turn off the input display
 *
 * @param      menu  The menu description struct
 *
 * @since      0.1
 */
void cc_displayTableMenu(cc_Menu* menu);

/*-------------------------------------------------------------------------*//**
 * @brief      Display the menu with the specified color style.
 *
 * @details    Allow the user to see and select a choice from the menu using the
 *             control keys, the user choice is the @c currentChoice field of
 *             the menu struct. This is a blocking function, return when the
 *             user press enter (or escape if the @c choiceOnEscape field of the
 *             menu struct is a valid choice).
 *
 *             Note: turn off the input display
 *
 * @param      menu    The menu description struct
 * @param[in]  colors  The color style definition
 *
 * @since      0.1
 */
void cc_displayColorMenu(cc_Menu* menu, const cc_MenuColors* colors);

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLUI_H
