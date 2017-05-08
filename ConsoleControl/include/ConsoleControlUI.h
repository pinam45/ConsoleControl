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
#include <ConsoleControlMessage.h>

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
 *             Note: turn off the inputs display and the cursor visibility
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
 *             Note: turn off the inputs display and the cursor visibility
 *
 * @param      menu    The menu description struct
 * @param[in]  colors  The color style definition
 *
 * @since      0.1
 */
void cc_displayColorMenu(cc_Menu* menu, const cc_MenuColors* colors);

/*-------------------------------------------------------------------------*//**
 * @brief      Display the message with the table style ('-' for horizontal
 *             lines, '|' for vertical lines, '+' for angles and intersections).
 *
 * @details    Allow the user to see the message and, if there is choices in the
 *             struct, select a choice using the control keys, the user choice
 *             is the @c currentChoice field of the message struct. This is a
 *             blocking function, return when the user press enter or escape if
 *             the @c canEscape field of the message struct is set to true. If
 *             there is no choices, or the user quit the message with escape, @c
 *             currentChoice fields of the message struct is set to @c
 *             NO_CHOICE.
 *
 *             Note: turn off the inputs display and the cursor visibility
 *
 * @param      message  The message description struct
 *
 * @since      0.2
 */
void cc_displayTableMessage(cc_Message* message);

/*-------------------------------------------------------------------------*//**
 * @brief      Display the message with the specified color style.
 *
 * @details    Allow the user to see the message and, if there is choices in the
 *             struct, select a choice using the control keys, the user choice
 *             is the @c currentChoice field of the message struct. This is a
 *             blocking function, return when the user press enter or escape if
 *             the @c canEscape field of the message struct is set to true. If
 *             there is no choices, or the user quit the message with escape, @c
 *             currentChoice fields of the message struct is set to @c
 *             NO_CHOICE.
 *
 *             Note: turn off the inputs display and the cursor visibility
 *
 * @param      message  The message description struct
 * @param[in]  colors   The color style definition
 *
 * @since      0.2
 */
void cc_displayColorMessage(cc_Message* message, const cc_MessageColors* colors);

/*-------------------------------------------------------------------------*//**
 * @brief      Display the option menu with the table style ('-' for horizontal
 *             lines, '|' for vertical lines, '+' for angles and intersections).
 *
 * @details    Allow the user to see and select options from the menu using the
 *             control keys, the selected option number is the @c selectedOption
 *             field of the option menu struct. This is a blocking function,
 *             return when the user select exit (which text is the @c exitText
 *             field of the struct) and press enter or press escape. If the user
 *             exited with the escape key the @c hasEscaped field of the struct
 *             is set to @c true.
 *
 * @param      optionsMenu  The options menu description struct
 *
 * @since      0.2
 */
void cc_displayTableOptionMenu(cc_OptionsMenu* optionsMenu);

/*-------------------------------------------------------------------------*//**
 * @brief      Display the option menu with the specified color style.
 *
 * @details    Allow the user to see and select options from the menu using the
 *             control keys, the selected option number is the @c selectedOption
 *             field of the option menu struct. This is a blocking function,
 *             return when the user select exit (which text is the @c exitText
 *             field of the struct) and press enter or press escape. If the user
 *             exited with the escape key the @c hasEscaped field of the struct
 *             is set to @c true.
 *
 * @param      optionsMenu  The options menu description struct
 * @param[in]  colors       The color style definition
 *
 * @since      0.2
 */
void cc_displayColorOptionMenu(cc_OptionsMenu* optionsMenu, const cc_MenuColors* colors);

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLUI_H
