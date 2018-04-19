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
 * @file ConsoleControlUtility.h
 * @brief      Definition of ConsoleControl utility functions to draw in the
 *             console.
 * @author     Maxime Pinard
 *
 * @since      0.1
 */

#ifndef CONSOLECONTROL_CONSOLECONTROLUTILITY_H
#define CONSOLECONTROL_CONSOLECONTROLUTILITY_H


#ifdef __cplusplus
extern "C" {
#endif

#include <ConsoleControl.h>

/*-------------------------------------------------------------------------*//**
 * @brief      Draw the outline of a rectangle.
 *
 * @param[in]  topLeft    Position of the top left corner of the rectangle
 * @param[in]  downRight  Position of the down right corner of the rectangle
 * @param[in]  ch         Character used to draw the rectangle
 *
 * @since      0.1
 */
void cc_drawRectangle(cc_Handle cch, cc_Vector2 topLeft, cc_Vector2 downRight, const char ch);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw the outline of a rectangle with the table style ('-' for
 *             horizontal lines, '|' for vertical lines, '+' for angles and
 *             intersections)
 *
 * @param[in]  topLeft    Position of the top left corner of the rectangle
 * @param[in]  downRight  Position of the down right corner of the rectangle
 *
 * @since      0.1
 */
void cc_drawTableRectangle(cc_Handle cch, cc_Vector2 topLeft, cc_Vector2 downRight);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw a filled rectangle.
 *
 * @param[in]  topLeft    Position of the top left corner of the rectangle
 * @param[in]  downRight  Position of the down right corner of the rectangle
 * @param[in]  ch         Character used to draw the rectangle
 *
 * @since      0.1
 */
void cc_drawFullRectangle(cc_Handle cch, cc_Vector2 topLeft, cc_Vector2 downRight, const char ch);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw a line with a character.
 *
 * @param[in]  from  Starting point of the line
 * @param[in]  to    Ending point of the line
 * @param[in]  ch    Character used to draw the line
 *
 * @since      0.1
 */
void cc_drawLine(cc_Handle cch, cc_Vector2 from, cc_Vector2 to, const char ch);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw a line with the horizontal table style ('-' for the line,
 *             '+' for the ends)
 *
 * @param[in]  from  Starting point of the line
 * @param[in]  to    Ending point of the line
 *
 * @since      0.1
 */
void cc_drawTableHorizontalLine(cc_Handle cch, cc_Vector2 from, cc_Vector2 to);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw a line with the vertical table style ('|' for the line, '+'
 *             for the ends)
 *
 * @param[in]  from  Starting point of the line
 * @param[in]  to    Ending point of the line
 *
 * @since      0.1
 */
void cc_drawTableVerticalLine(cc_Handle cch, cc_Vector2 from, cc_Vector2 to);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw a line with a pattern of characters.
 *
 * @param[in]  from     Starting point of the line
 * @param[in]  to       Ending point of the line
 * @param[in]  pattern  The pattern used to draw the line
 *
 * @since      0.1
 */
void cc_drawPatternLine(cc_Handle cch, cc_Vector2 from, cc_Vector2 to, const char* pattern);

/*-------------------------------------------------------------------------*//**
 * @brief      Draw a circle.
 *
 * @param[in]  center  Position of the center
 * @param[in]  radius  The radius
 * @param[in]  ch      Character used to draw the circle
 *
 * @since      0.1
 */
void cc_drawCircle(cc_Handle cch, cc_Vector2 center, unsigned int radius, char ch);

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROLUTILITY_H
