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
 * @file ConsoleControlInput.h
 * @brief      cc_Key enum and cc_Input struct definition.
 * @author     Maxime Pinard
 *
 * @since      0.1
 */

#ifndef CONSOLECONTROL_CONSOLECONTROLINPUT_H
#define CONSOLECONTROL_CONSOLECONTROLINPUT_H


#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------*//**
 * @enum cc_Key
 *
 * @brief      Keyboards keys used with ConsoleControl.
 *
 * @since      0.1
 */
typedef enum{
	HOME_KEY, /**< Home key */
	END_KEY, /**< End key */
	PAGE_UP_KEY, /**< Page up key */
	PAGE_DOWN_KEY, /**< Page down key */
	UP_ARROW_KEY, /**< Up arrow key */
	DOWN_ARROW_KEY, /**< Down arrow key */
	LEFT_ARROW_KEY, /**< Left arrow key */
	RIGHT_ARROW_KEY, /**< Right arrow key */
	BACKSPACE_KEY, /**< Backspace key */
	TAB_KEY, /**< Tab key */
	ENTER_KEY, /**< Enter / Carriage return key */
	ESC_KEY, /**< Escape key */
	SPACE_KEY, /**< Space key / Space bar */
	INS_KEY, /**< Insert key */
	DEL_KEY, /**< Delete key */
	F1_KEY, /**< F1 key */
	F2_KEY, /**< F2 key */
	F3_KEY, /**< F3 key */
	F4_KEY, /**< F4 key */
	F5_KEY, /**< F5 key */
	F6_KEY, /**< F6 key */
	F7_KEY, /**< F7 key */
	F8_KEY, /**< F8 key */
	F9_KEY, /**< F9 key */
	F10_KEY, /**< F10 key */
	F11_KEY, /**< F11 key */
	F12_KEY, /**< F12 key */
	OTHER_KEY, /**< Other key */
}cc_Key;

/*-------------------------------------------------------------------------*//**
 * @struct cc_Input
 *
 * @brief      Inputs used with ConsoleControl.
 *
 * @since      0.1
 */
typedef struct{
	cc_Key key; /**< The key pressed */
	char ch; /**< The character that correspond to the key pressed */
}cc_Input;

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLINPUT_H
