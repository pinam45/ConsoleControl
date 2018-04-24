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
 * @file ConsoleControl.h
 * @brief      Definition of ConsoleControl related functions.
 * @author     Maxime Pinard
 *
 * @since      0.1
 */

#ifndef CONSOLECONTROL_CONSOLECONTROL_H
#define CONSOLECONTROL_CONSOLECONTROL_H


#ifdef __cplusplus
extern "C" {
#endif

#include <definitions/ConsoleControlColor.h>
#include <definitions/ConsoleControlInput.h>

#include <stdbool.h>

/*-------------------------------------------------------------------------*//**
 * @brief      ConsoleControl handle type.
 *
 * @since      0.3
 */
typedef void* cc_Handle;

/*-------------------------------------------------------------------------*//**
 * @struct cc_Vector2
 *
 * @brief      2D vector used with ConsoleControl.
 *
 * @since      0.1
 */
typedef struct {
	int x; /**< x coordinate of the vector */
	int y; /**< y coordinate of the vector */
} cc_Vector2;

/*-------------------------------------------------------------------------*//**
 * @brief      Strart ConsoleControl, initialise the handle.
 *
 * @return     The ConsoleControl handle
 *
 * @since      0.3
 */
cc_Handle cc_start();

/*-------------------------------------------------------------------------*//**
 * @brief      End ConsoleControl, delete the handle. Warning: after calling
 *             this function the handle is no longer valid.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @since      0.3
 */
void cc_end(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the console output foreground color.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  color  The color
 *
 * @since      0.1
 */
void cc_setForegroundColor(cc_Handle cch, cc_Color color);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the console output background color.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  color  The color
 *
 * @since      0.1
 */
void cc_setBackgroundColor(cc_Handle cch, cc_Color color);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the console output background and foreground color.
 *
 * @param[in]  cch              The ConsoleControl handle
 * @param[in]  backgroundColor  The background color
 * @param[in]  foregroundColor  The foreground color
 *
 * @since      0.1
 */
void cc_setColors(cc_Handle cch, cc_Color backgroundColor, cc_Color foregroundColor);

/*-------------------------------------------------------------------------*//**
 * @brief      Get the console window width.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @return     The console width
 *
 * @since      0.1
 */
int cc_getWidth(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Get the console window height.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @return     The console height
 *
 * @since      0.1
 */
int cc_getHeight(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the cursor position in the console window.
 *
 * @param[in]  cch       The ConsoleControl handle
 * @param[in]  position  The position
 *
 * @since      0.1
 */
void cc_setCursorPosition(cc_Handle cch, cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps up.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorUp(cc_Handle cch, int steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps down.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorDown(cc_Handle cch, int steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps left.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorLeft(cc_Handle cch, int steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps right.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorRight(cc_Handle cch, int steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps horizontally.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorHorizontally(cc_Handle cch, int steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps vertically.
 *
 * @param[in]  cch    The ConsoleControl handle
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorVertically(cc_Handle cch, int steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor.
 *
 * @param[in]  cch   The ConsoleControl handle
 * @param[in]  move  The move
 *
 * @since      0.1
 */
void cc_moveCursor(cc_Handle cch, cc_Vector2 move);

/*-------------------------------------------------------------------------*//**
 * @brief      Save the cursor position.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @since      0.1
 */
void cc_saveCursorPosition(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Restore the cursor position.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @since      0.1
 */
void cc_restoreCursorPosition(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the cursor visibility.
 *
 * @param[in]  cch         The ConsoleControl handle
 * @param[in]  visibility  True for visible, false for not visible
 *
 * @since      0.2
 */
void cc_setCursorVisibility(cc_Handle cch, bool visibility);

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the position in the console window.
 *
 * @param[in]  cch       The ConsoleControl handle
 * @param[in]  position  The position
 *
 * @return     The position clamped down in the console window
 *
 * @since      0.1
 */
cc_Vector2 cc_clamp(cc_Handle cch, cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the x coordinate in the console window.
 *
 * @param[in]  cch   The ConsoleControl handle
 * @param[in]  x     The x coordinate
 *
 * @return     The x coordinate clamped down in the console window
 *
 * @since      0.1
 */
int cc_clampX(cc_Handle cch, int x);

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the y coordinate in the console window.
 *
 * @param[in]  cch   The ConsoleControl handle
 * @param[in]  y     The y coordinate
 *
 * @return     The y coordinate clamped down in the console window
 *
 * @since      0.1
 */
int cc_clampY(cc_Handle cch, int y);

/*-------------------------------------------------------------------------*//**
 * @brief      Determine if the console window contains the position
 *
 * @param[in]  cch       The ConsoleControl handle
 * @param[in]  position  The position
 *
 * @return     True if the console window contains the position, false otherwise
 *
 * @since      0.1
 */
bool cc_contains(cc_Handle cch, cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Clean the console windows.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @since      0.1
 */
void cc_clean(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Clean the complete console.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @since      0.1
 */
void cc_completeClean(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Instantly get an inputed char without waiting a carriage return.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @return     The char
 *
 * @since      0.1
 */
char cc_instantGetChar(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Check if an input if waiting.
 *
 * @details    The input can be taken with @c cc_instantGetChar.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @return     True if an input if waiting, false otherwise.
 *
 * @since      0.1
 */
bool cc_waitingInput(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Set if the inputs must be displayed or not.
 *
 * @param[in]  cch      The ConsoleControl handle
 * @param[in]  display  True for display, false for no display
 *
 * @since      0.1
 */
void cc_displayInputs(cc_Handle cch, bool display);

/*-------------------------------------------------------------------------*//**
 * @brief      Get an input. Blocking function.
 *
 * @param[in]  cch   The ConsoleControl handle
 *
 * @return     The input
 *
 * @since      0.1
 */
cc_Input cc_getInput(cc_Handle cch);

/*-------------------------------------------------------------------------*//**
 * @brief      Print a character in place, without moving the cursor.
 *
 * @param[in]  cch   The ConsoleControl handle
 * @param[in]  c     The character to print
 *
 * @since      0.1
 */
void cc_printInPlace(cc_Handle cch, char c);

/*-------------------------------------------------------------------------*//**
 * @brief      Get the character associated with the key.
 *
 * @param[in]  cch   The ConsoleControl handle
 * @param[in]  key   The key
 *
 * @return     The character associated with the key
 *
 * @since      0.1
 */
char cc_getAssociatedChar(cc_Handle cch, cc_Key key);

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROL_H
