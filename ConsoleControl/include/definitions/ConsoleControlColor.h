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
typedef enum {
	CC_BLACK, /**< Black color */
	CC_BLUE, /**< Blue color */
	CC_GREEN, /**< Green color */
	CC_CYAN, /**< Cyan color */
	CC_RED, /**< Red color */
	CC_MAGENTA, /**< Magenta color */
	CC_YELLOW, /**< Yellow color */
	CC_WHITE, /**< White color */
	CC_LIGHT_BLACK, /**< Light black color */
	CC_LIGHT_BLUE, /**< Light blue color */
	CC_LIGHT_GREEN, /**< Light green color */
	CC_LIGHT_CYAN, /**< Light cyan color */
	CC_LIGHT_RED, /**< Light red color */
	CC_LIGHT_MAGENTA, /**< Light magenta color */
	CC_LIGHT_YELLOW, /**< Light yellow color */
	CC_LIGHT_WHITE /**< Light white color */
} cc_Color;

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLCOLOR_H
