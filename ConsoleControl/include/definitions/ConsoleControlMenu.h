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

#include <definitions/ConsoleControlColor.h>

#include <stdbool.h>

/*-------------------------------------------------------------------------*//**
 * @struct cc_Menu
 *
 * @brief      Definition of a menu.
 *
 * @since      0.1
 */
typedef struct {
	const char* title; /**< Title (without '\\n' or '\\r') */
	const char** choices; /**< Possible choices (without '\\n' or '\\r') */
	unsigned int choicesNumber; /**< Number of choices */
	unsigned int currentChoice; /**< Current choice number */
	int choiceOnEscape;  /**< Choice to select when the escape key is pressed (do nothing:
	                      * number out of choices range like -1) */
} cc_Menu;

/*-------------------------------------------------------------------------*//**
 * @struct cc_ChoicesOption
 *
 * @brief      Definition of a choices option.
 *
 * @since      0.2
 */
typedef struct {
	const char** choices; /**< Possible choices (without '\\n' or '\\r') */
	unsigned int choicesNumber; /**< Number of choices */
	unsigned int currentChoice; /**< Current choice number */
} cc_ChoicesOption;

/*-------------------------------------------------------------------------*//**
 * @struct cc_IntegerOption
 *
 * @brief      Definition of a integer option.
 *
 * @since      0.2
 */
typedef struct {
	int value; /**< Value of the option */
	int minValue; /**< Minimal value */
	int maxValue; /**< Maximal value */
	int step; /**< Value change step */
} cc_IntegerOption;

/*-------------------------------------------------------------------------*//**
 * @struct cc_CharacterOption
 *
 * @brief      Definition of a character option.
 *
 * @since      0.2
 */
typedef struct {
	char value; /**< Value of the option */
	char minValue; /**< Minimal value */
	char maxValue; /**< Maximal value */
} cc_CharacterOption;

/*-------------------------------------------------------------------------*//**
 * @struct cc_OptionType
 *
 * @brief      Definition of an option type.
 *
 * @since      0.2
 */
typedef enum {
	CHOICES_OPTION, /**< Choices option (@c cc_ChoicesOption) */
	INTEGER_OPTION, /**< Integer option (@c cc_IntegerOption) */
	CHARACTER_OPTION /**< Character option (@c cc_CharacterOption) */
} cc_OptionType;

/*-------------------------------------------------------------------------*//**
 * @struct cc_Option
 *
 * @brief      Definition of an option.
 *
 * @since      0.2
 */
typedef struct {
	const char* name; /**< Name (without '\\n' or '\\r') */
	cc_OptionType optionType; /**< Type */
	union {
		cc_ChoicesOption* choicesOption; /**< Choices option */
		cc_IntegerOption* integerOption; /**< Integer option */
		cc_CharacterOption* characterOption; /**< Character option */
	};
} cc_Option;

/*-------------------------------------------------------------------------*//**
 * @struct cc_OptionsMenu
 *
 * @brief      Definition of an options menu.
 *
 * @since      0.2
 */
typedef struct {
	const char* title; /**< Title (without '\\n' or '\\r') */
	cc_Option** options; /**< Options */
	unsigned int optionsNumber; /**< Number of options */
	unsigned int selectedOption; /**< Selected option number (@c optionsNumber for exit) */
	const char* exitText; /**< Exit text */
	bool hasEscaped; /**< True if the user exited with the escape key */
} cc_OptionsMenu;

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
