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
 * @file ConsoleControlMessage.h
 * @brief      ConsoleControl messages related structs and enums definition.
 * @author     Maxime Pinard
 *
 * @since      0.2
 */

#ifndef CONSOLECONTROL_C_CONSOLECONTROLMESSAGE_H
#define CONSOLECONTROL_C_CONSOLECONTROLMESSAGE_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <ConsoleControlColor.h>

/*-------------------------------------------------------------------------*//**
 * @struct cc_MessageChoice
 *
 * @brief      Definition of a message choice.
 *
 * @since      0.2
 */
typedef enum {
	LEFT_CHOICE, /**< Left choice */
	MIDDLE_CHOICE, /**< Middle choice */
	RIGHT_CHOICE, /**< Right choice */
	NO_CHOICE /**< Quit without choosing */
} cc_MessageChoice;

/*-------------------------------------------------------------------------*//**
 * @struct cc_Message
 *
 * @brief      Definition of a message.
 *
 * @since      0.2
 */
typedef struct {
	const char* title; /**< Title (without '\\n' or '\\r'), for no title: NULL or empty string */
	const char* message; /**< Message (without '\\r', can contain '\\n') */
	const char* leftChoice; /**< Left choice (without '\\n' or '\\r'), for no choice: NULL or empty string */
	const char* middleChoice; /**< Middle choice (without '\\n' or '\\r'), for no choice: NULL or empty string */
	const char* rightChoice; /**< Right choice (without '\\n' or '\\r'), for no choice: NULL or empty string */
	cc_MessageChoice currentChoice; /**< Current choice */
	bool canEscape; /**< Can use escape key to exit without choosing */
} cc_Message;

/*-------------------------------------------------------------------------*//**
 * @struct cc_MessageColors
 *
 * @brief      Definition of a message color style.
 *
 * @since      0.2
 */
typedef struct {
	cc_Color mainBackgroundColor; /**< Main background color **/
	cc_Color titleBackgroundColor; /**< Title background color */
	cc_Color titleForegroundColor; /**< Title foreground color */
	cc_Color messageBackgroundColor; /**< Message background color */
	cc_Color messageForegroundColor; /**< Message foreground color */
	cc_Color choicesBackgroundColor; /**< Choices background color */
	cc_Color choicesForegroundColor; /**< Choices foreground color */
	cc_Color selectionBackgroundColor;  /**< Selection background color */
	cc_Color selectionForegroundColor;  /**< Selection foreground color */
} cc_MessageColors;

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_C_CONSOLECONTROLMESSAGE_H
