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
 * @file ConsoleControlMenu.h
 * @brief      ConsoleControl menus related structs definition.
 * @author     Maxime Pinard
 *
 * @since      0.1
 */

#ifndef CONSOLECONTROL_CONSOLECONTROLMENU_H
#define CONSOLECONTROL_CONSOLECONTROLMENU_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <ConsoleControlColor.h>

/*-------------------------------------------------------------------------*//**
 * @struct cc_Menu
 *
 * @brief      Definition of a menu.
 *
 * @since      0.1
 */
typedef struct {
	const char* title; /**< Title */
	const char** choices; /**< Possible choices (without '\n' or '\r') */
	unsigned int choicesNumber; /**< Number of choices */
	unsigned int currentChoice; /**< Current choice number */
	int choiceOnEscape;  /**< Choice to select when the escape key is pressed (do nothing:
	                      * number out of choices range like -1) */
} cc_Menu;

/*-------------------------------------------------------------------------*//**
 * @struct cc_MenuColors
 *
 * @brief      Definition of a menu color style.
 *
 * @since      0.1
 */
typedef struct {
	cc_Color mainBackgroundColor; /**< Main background color **/
	cc_Color titleBackgroundColor; /**< Title background color */
	cc_Color titleForegroundColor; /**< Title foreground color */
	cc_Color choicesBackgroundColor; /**< Choices background color */
	cc_Color choicesForegroundColor; /**< Choices foreground color */
	cc_Color selectionBackgroundColor;  /**< Selection background color */
	cc_Color selectionForegroundColor;  /**< Selection foreground color */
} cc_MenuColors;

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLMENU_H
