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
 * @file ConsoleControlColor.h
 * @brief      cc_Color struct definition.
 * @author     Maxime Pinard
 *
 * @since      0.1
 */

#ifndef CONSOLECONTROL_CONSOLECONTROLCOLOR_H
#define CONSOLECONTROL_CONSOLECONTROLCOLOR_H


#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------*//**
 * @enum cc_Color
 *
 * @brief      Colors used with ConsoleControl.
 *
 * @since      0.1
 */
typedef enum{
	BLACK, /**< Black color */
	BLUE, /**< Blue color */
	GREEN, /**< Green color */
	CYAN, /**< Cyan color */
	RED, /**< Red color */
	MAGENTA, /**< Magenta color */
	YELLOW, /**< Yellow color */
	WHITE, /**< White color */
	LIGHT_BLACK, /**< Light black color */
	LIGHT_BLUE, /**< Light blue color */
	LIGHT_GREEN, /**< Light green color */
	LIGHT_CYAN, /**< Light cyan color */
	LIGHT_RED, /**< Light red color */
	LIGHT_MAGENTA, /**< Light magenta color */
	LIGHT_YELLOW, /**< Light yellow color */
	LIGHT_WHITE /**< Light white color */
}cc_Color;

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLCOLOR_H
