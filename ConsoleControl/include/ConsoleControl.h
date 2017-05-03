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

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define OS_WINDOWS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <log.h>
#include <ConsoleControlColor.h>
#include <ConsoleControlInput.h>

#ifdef OS_WINDOWS

#include <windows.h>

#else //OS_WINDOWS

#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define CSI "\033[" //Control Sequence Introducer

//Moves the cursor n (default 1) cells in the given direction.
//If the cursor is already at the edge of the screen, this has no effect.
#define CUU_CODE "A" //Cursor Up, CSI n A
#define CUD_CODE "B" //Cursor Down, CSI n B
#define CUF_CODE "C" //Cursor Forward, CSI n C
#define CUB_CODE "D" //Cursor Back, CSI n D

//Moves cursor to beginning of the line n (default 1) lines down.
#define CNL_CODE "E" //Cursor Next Line, CSI n E

//Moves cursor to beginning of the line n (default 1) lines up.
#define CPL_CODE "F" //Cursor Previous Line, CSI n F

//Moves the cursor to column n (default 1).
#define CHA_CODE "G" //Cursor Horizontal Absolute, CSI n G

//Moves the cursor to row n, column m.
//The values are 1-based, and default to 1 (top left corner) if omitted.
#define CUP_CODE "H" //Cursor Position, CSI n ; m H

//Clears part of the screen. If n is 0 (or missing), clear from cursor to end of screen.
// If n is 1, clear from cursor to beginning of the screen.
// If n is 2, clear entire screen.
// If n is 3, clear entire screen and delete all lines saved in the scrollback buffer.
#define ED_CODE "J" //Erase in Display, CSI n J

//Erases part of the line.
//If n is zero (or missing), clear from cursor to the end of the line.
//If n is one, clear from cursor to beginning of the line.
//If n is two, clear entire line.
//Cursor position does not change.
#define EL_CODE "K" //Erase in Line, CSI n K

//Scroll whole page up by n (default 1) lines.
//New lines are added at the bottom.
#define SU_CODE "S" //Scroll Up, CSI n S

//Scroll whole page down by n (default 1) lines.
//New lines are added at the top.
#define SD_CODE "T" //Scroll Down, CSI n T

//Moves the cursor to row n, column m.
//Both default to 1 if omitted. Same as CUP.
#define HVP_CODE "f" //Horizontal and Vertical Position, CSI n ; m f

//Sets SGR parameters, including text color.
//After CSI can be zero or more parameters separated with ;.
//With no parameters, CSI m is treated as CSI 0 m (reset / normal).
#define SGR_CODE "m" //Select Graphic Rendition, CSI n m

//Saves the cursor position.
#define SCP_CODE "s" //Save Cursor Position, CSI s

//Restores the cursor position.
#define RCP_CODE "u" //Restore Cursor Position, CSI u

//Hides the cursor.
#define DECTCEM_H_CODE "?25l" //DECTCEM Hide, CSI ?25l

//Shows the cursor.
#define DECTCEM_S_CODE "?25h" //DECTCEM Show, CSI ?25h

//Use with SGR_CODE as n value.
//Inverse or reverse; swap foreground and background (reverse video).
#define SGR_REVERSE_VALUE "7" //CSI SGR_REVERSE_VALUE SGR_CODE

#endif //OS_WINDOWS

/*-------------------------------------------------------------------------*//**
 * Integral data type used with ConsoleControl.
 *
 * @since      0.1
 */
typedef int cc_type;

/*-------------------------------------------------------------------------*//**
 * @struct cc_Vector2
 *
 * @brief      2D vector used with ConsoleControl.
 *
 * @since      0.1
 */
typedef struct {
	cc_type x; /**< x coordinate of the vector */
	cc_type y; /**< y coordinate of the vector */
} cc_Vector2;

/*-------------------------------------------------------------------------*//**
 * @brief      Set the console output foreground color.
 *
 * @param[in]  color  The color
 *
 * @since      0.1
 */
void cc_setForegroundColor(cc_Color color);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the console output background color.
 *
 * @param[in]  color  The color
 *
 * @since      0.1
 */
void cc_setBackgroundColor(cc_Color color);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the console output background and foreground color.
 *
 * @param[in]  backgroundColor  The background color
 * @param[in]  foregroundColor  The foreground color
 *
 * @since      0.1
 */
void cc_setColors(cc_Color backgroundColor, cc_Color foregroundColor);

/*-------------------------------------------------------------------------*//**
 * @brief      Get the console window width.
 *
 * @return     The console width
 *
 * @since      0.1
 */
cc_type cc_getWidth();

/*-------------------------------------------------------------------------*//**
 * @brief      Get the console window height.
 *
 * @return     The console height
 *
 * @since      0.1
 */
cc_type cc_getHeight();

/*-------------------------------------------------------------------------*//**
 * @brief      Set the cursor position in the console window.
 *
 * @param[in]  position  The position
 *
 * @since      0.1
 */
void cc_setCursorPosition(cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps up.
 *
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorUp(cc_type steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps down.
 *
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorDown(cc_type steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps left.
 *
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorLeft(cc_type steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps right.
 *
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorRight(cc_type steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps horizontally.
 *
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorHorizontally(cc_type steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor @p steps steps vertically.
 *
 * @param[in]  steps  The steps
 *
 * @since      0.1
 */
void cc_moveCursorVertically(cc_type steps);

/*-------------------------------------------------------------------------*//**
 * @brief      Move the cursor.
 *
 * @param[in]  move  The move
 *
 * @since      0.1
 */
void cc_moveCursor(cc_Vector2 move);

/*-------------------------------------------------------------------------*//**
 * @brief      Save the cursor position.
 *
 * @since      0.1
 */
void cc_saveCursorPosition();

/*-------------------------------------------------------------------------*//**
 * @brief      Restore the cursor position.
 *
 * @since      0.1
 */
void cc_restoreCursorPosition();

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the position in the console window.
 *
 * @param[in]  position  The position
 *
 * @return     The position clamped down in the console window
 *
 * @since      0.1
 */
cc_Vector2 cc_clamp(cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the x coordinate in the console window.
 *
 * @param[in]  x     The x coordinate
 *
 * @return     The x coordinate clamped down in the console window
 *
 * @since      0.1
 */
cc_type cc_clampX(cc_type x);

/*-------------------------------------------------------------------------*//**
 * @brief      Clamp down the y coordinate in the console window.
 *
 * @param[in]  y     The y coordinate
 *
 * @return     The y coordinate clamped down in the console window
 *
 * @since      0.1
 */
cc_type cc_clampY(cc_type y);

/*-------------------------------------------------------------------------*//**
 * @brief      Determine if the console window contains the position
 *
 * @param[in]  position  The position
 *
 * @return     True if the console window contains the position, false otherwise
 *
 * @since      0.1
 */
bool cc_contains(cc_Vector2 position);

/*-------------------------------------------------------------------------*//**
 * @brief      Clean the console windows.
 *
 * @since      0.1
 */
void cc_clean();

/*-------------------------------------------------------------------------*//**
 * @brief      Clean the complete console.
 *
 * @since      0.1
 */
void cc_completeClean();

/*-------------------------------------------------------------------------*//**
 * @brief      Instantly get an inputed char without waiting a carriage return.
 *
 * @return     The char
 *
 * @since      0.1
 */
char cc_instantGetChar();

/*-------------------------------------------------------------------------*//**
 * @brief      Check if an input if waiting.
 *
 * @details    The input can be taken with @c cc_instantGetChar.
 *
 * @return     True if an input if waiting, false otherwise.
 *
 * @since      0.1
 */
bool cc_waitingInput();

/*-------------------------------------------------------------------------*//**
 * @brief      Set if the inputs must be displayed or not.
 *
 * @param[in]  display  True for display, false for no display
 *
 * @since      0.1
 */
void cc_displayInputs(bool display);

/*-------------------------------------------------------------------------*//**
 * @brief      Get an input. Blocking function.
 *
 * @return     The input
 *
 * @since      0.1
 */
cc_Input cc_getInput();

/*-------------------------------------------------------------------------*//**
 * @brief      Print a character in place, without moving the cursor.
 *
 * @param[in]  c     The character to print
 *
 * @since      0.1
 */
void cc_printInPlace(char c);

/*-------------------------------------------------------------------------*//**
 * @brief      Get the character associated with the key.
 *
 * @param[in]  key   The key
 *
 * @return     The character associated with the key
 *
 * @since      0.1
 */
char cc_getAssociatedChar(cc_Key key);

#ifdef __cplusplus
}
#endif


#endif //CONSOLECONTROL_CONSOLECONTROL_H
