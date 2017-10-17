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

#include <ConsoleControl.h>

#ifdef _WIN32

#include <WindowsConsoleControl.h>

#include <ConsoleControlColor.h>
#include <ConsoleControlInput.h>
#include <log.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <windows.h>

// For cc_saveCursorPosition and cc_restoreCursorPosition
static cc_Vector2 savedPosition = {0, 0};

static WORD cc_getForegroundColorIdentifier(cc_Color color);

static WORD cc_getBackgroundColorIdentifier(cc_Color color);

WORD cc_getForegroundColorIdentifier(cc_Color color) {
	WORD colorIdentifier = 0;
	switch(color) {
		case CC_LIGHT_BLUE:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_BLUE:
			colorIdentifier |= FOREGROUND_BLUE;
			break;
		case CC_LIGHT_GREEN:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_GREEN:
			colorIdentifier |= FOREGROUND_GREEN;
			break;
		case CC_LIGHT_CYAN:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_CYAN:
			colorIdentifier |= FOREGROUND_BLUE | FOREGROUND_GREEN;
			break;
		case CC_LIGHT_RED:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_RED:
			colorIdentifier |= FOREGROUND_RED;
			break;
		case CC_LIGHT_MAGENTA:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_MAGENTA:
			colorIdentifier |= FOREGROUND_BLUE | FOREGROUND_RED;
			break;
		case CC_LIGHT_YELLOW:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_YELLOW:
			colorIdentifier |= FOREGROUND_GREEN | FOREGROUND_RED;
			break;
		case CC_LIGHT_WHITE:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_WHITE:
			colorIdentifier |= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
			break;
		case CC_LIGHT_BLACK:
			colorIdentifier |= FOREGROUND_INTENSITY;
			break;
		case CC_BLACK:
			/* FALLTHROUGH */
		default:
			break;
	}
	return colorIdentifier;
}

WORD cc_getBackgroundColorIdentifier(cc_Color color) {
	WORD colorIdentifier = 0;
	switch(color) {
		case CC_LIGHT_BLUE:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_BLUE:
			colorIdentifier |= BACKGROUND_BLUE;
			break;
		case CC_LIGHT_GREEN:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_GREEN:
			colorIdentifier |= BACKGROUND_GREEN;
			break;
		case CC_LIGHT_CYAN:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_CYAN:
			colorIdentifier |= BACKGROUND_BLUE | BACKGROUND_GREEN;
			break;
		case CC_LIGHT_RED:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_RED:
			colorIdentifier |= BACKGROUND_RED;
			break;
		case CC_LIGHT_MAGENTA:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_MAGENTA:
			colorIdentifier |= BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case CC_LIGHT_YELLOW:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_YELLOW:
			colorIdentifier |= BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case CC_LIGHT_WHITE:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CC_WHITE:
			colorIdentifier |= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case CC_LIGHT_BLACK:
			colorIdentifier |= BACKGROUND_INTENSITY;
			break;
		case CC_BLACK:
			/* FALLTHROUGH */
		default:
			break;
	}
	return colorIdentifier;
}

// functions from ConsoleControl.h

void cc_setForegroundColor(const cc_Color color) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut,
	                            (csbi.wAttributes /* current colors */
	                             & cc_getBackgroundColorIdentifier(CC_LIGHT_WHITE)) /* only keep background */
	                            | cc_getForegroundColorIdentifier(color)) /* change foreground */) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setBackgroundColor(const cc_Color color) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut,
	                            (csbi.wAttributes /* current colors */
	                             & cc_getForegroundColorIdentifier(CC_LIGHT_WHITE)) /* only keep foreground */
	                            | cc_getBackgroundColorIdentifier(color)) /* change background */) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setColors(const cc_Color backgroundColor, const cc_Color foregroundColor) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut,
	                            cc_getBackgroundColorIdentifier(backgroundColor)
	                            | cc_getForegroundColorIdentifier(foregroundColor))) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

cc_type cc_getWidth() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

cc_type cc_getHeight() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void cc_setCursorPosition(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD pos = {
		(short) (position.x + csbi.srWindow.Left),
		(short) (position.y + csbi.srWindow.Top)
	};

	if(!SetConsoleCursorPosition(hStdOut, pos)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorUp(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y - steps)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorDown(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y + steps)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorLeft(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X - steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorRight(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorHorizontally(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorVertically(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y + steps)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursor(cc_Vector2 move) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + move.x),
		(SHORT) (csbi.dwCursorPosition.Y + move.y)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_saveCursorPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	savedPosition.x = csbi.dwCursorPosition.X - csbi.srWindow.Left;
	savedPosition.y = csbi.dwCursorPosition.Y - csbi.srWindow.Top;
}

void cc_restoreCursorPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(short) (savedPosition.x + csbi.srWindow.Left),
		(short) (savedPosition.y + csbi.srWindow.Top)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setCursorVisibility(bool visibility) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_CURSOR_INFO cci;
	if(!GetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERROR("GetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}

	if(visibility) {
		cci.bVisible = TRUE;
	}
	else {
		cci.bVisible = FALSE;
	}

	if(!SetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERROR("SetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}
}

cc_Vector2 cc_clamp(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return position;
	}

	short maxX = (short) (csbi.srWindow.Right - csbi.srWindow.Left);
	short maxY = (short) (csbi.srWindow.Bottom - csbi.srWindow.Top);
	cc_Vector2 result = {
		position.x < maxX ? (position.x < 0 ? 0 : position.x) : maxX,
		position.y < maxY ? (position.y < 0 ? 0 : position.y) : maxY
	};
	return result;
}

cc_type cc_clampX(cc_type x) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return x;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return x;
	}

	short maxX = (short) (csbi.srWindow.Right - csbi.srWindow.Left);
	return x < maxX ? (x < 0 ? 0 : x) : maxX;
}

cc_type cc_clampY(cc_type y) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return y;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return y;
	}

	short maxY = (short) (csbi.srWindow.Bottom - csbi.srWindow.Top - 1);
	return y < maxY ? (y < 0 ? 0 : y) : maxY;
}

bool cc_contains(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return false;
	}

	return position.x >= 0
	       && position.y >= 0
	       && position.x <= (csbi.srWindow.Right - csbi.srWindow.Left)
	       && position.y <= (csbi.srWindow.Bottom - csbi.srWindow.Top);
}

// credits: http://www.cplusplus.com/articles/4z18T05o/
void cc_clean() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	/* Compute the number of cells in the current screen */
	DWORD cellCount = (DWORD) ((csbi.srWindow.Right - csbi.srWindow.Left + (short) 1)
	                           * (csbi.srWindow.Bottom - csbi.srWindow.Top + (short) 1));

	/* Home is at the top left of the current screen */
	COORD homeCoords = {csbi.srWindow.Left, csbi.srWindow.Top};
	DWORD count;

	/* Fill the entire buffer with spaces */
	if(!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputCharacter failed (error %lu)", GetLastError());
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputAttribute failed (error %lu)", GetLastError());
		return;
	}

	/* Move the cursor home */
	if(!SetConsoleCursorPosition(hStdOut, homeCoords)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
	}
}

// credits: http://www.cplusplus.com/articles/4z18T05o/
void cc_completeClean() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	/* Get the number of cells in the current buffer */
	DWORD cellCount = (DWORD) (csbi.dwSize.X * csbi.dwSize.Y);

	COORD homeCoords = {0, 0};
	DWORD count;

	/* Fill the entire buffer with spaces */
	if(!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputCharacter failed (error %lu)", GetLastError());
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputAttribute failed (error %lu)", GetLastError());
		return;
	}

	/* Move the cursor home */
	if(!SetConsoleCursorPosition(hStdOut, homeCoords)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
	}
}

char cc_instantGetChar() {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	/* Save console mode */
	DWORD saveMode;
	if(!GetConsoleMode(hStdIn, &saveMode)) {
		LOG_ERROR("GetConsoleMode failed (error %lu)", GetLastError());
		return 0;
	}
	if(!SetConsoleMode(hStdIn, ENABLE_PROCESSED_INPUT)) {
		LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
		return 0;
	}

	TCHAR ch = 0;
	if(WaitForSingleObject(hStdIn, INFINITE) == WAIT_OBJECT_0) {
		DWORD num;
		if(!ReadConsole(hStdIn, &ch, 1, &num, NULL)) {
			LOG_ERROR("ReadConsole failed (error %lu)", GetLastError());
		}
		if(num != 1) {
			LOG_ERROR("Bad characters read number");
		}
	}
	else {
		LOG_ERROR("WaitForSingleObject failed (error %lu)", GetLastError());
	}

	/* Restore console mode */
	if(!SetConsoleMode(hStdIn, saveMode)) {
		LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
	}
	return ch;
}

bool cc_waitingInput() {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return false;
	}

	DWORD num;
	if(!GetNumberOfConsoleInputEvents(hStdIn, &num)) {
		LOG_ERROR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
		return false;
	}

	return (num > 1);
}

void cc_displayInputs(bool display) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	/* Get console mode */
	DWORD mode;
	if(!GetConsoleMode(hStdIn, &mode)) {
		LOG_ERROR("GetConsoleMode failed (error %lu)", GetLastError());
		return;
	}

	if(display) {
		/* Add echo input to the mode */
		if(!SetConsoleMode(hStdIn, mode | ENABLE_ECHO_INPUT)) {
			LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
			return;
		}
	}
	else {
		/* Remove echo input to the mode */
		if(!SetConsoleMode(hStdIn, mode & ~((DWORD) ENABLE_ECHO_INPUT))) {
			LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
			return;
		}
	}
}

static WORD processedInputsNb = 0;

cc_Input cc_getInput() {
	cc_Input input = {OTHER_KEY, 0};

	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return input;
	}
	DWORD num;

	/* Get number of input event */
	if(!GetNumberOfConsoleInputEvents(hStdIn, &num)) {
		LOG_ERROR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
		return input;
	}

	/* If there is no input event wait one */
	if(num < 1) {
		if(WaitForSingleObject(hStdIn, INFINITE) != WAIT_OBJECT_0) {
			LOG_ERROR("WaitForSingleObject failed (error %lu)", GetLastError());
			return input;
		}
	}

	/* Read the first event that is a key pressed event */
	INPUT_RECORD event;
	if(!PeekConsoleInput(hStdIn, &event, 1, &num)) {
		LOG_ERROR("PeekConsoleInput failed (error %lu)", GetLastError());
		return input;
	}
	if(num < 1) {
		LOG_ERROR("WaitForSingleObject returned without an input event");
		return input;
	}
	while(event.EventType != KEY_EVENT || !event.Event.KeyEvent.bKeyDown) {
		/* Not a key pressed event, remove it from the console input buffer */
		if(!ReadConsoleInput(hStdIn, &event, 1, &num)) {
			LOG_ERROR("ReadConsoleInput failed (error %lu)", GetLastError());
			return input;
		}

		/* Get number of input event */
		if(!GetNumberOfConsoleInputEvents(hStdIn, &num)) {
			LOG_ERROR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
			return input;
		}

		/* If there is no input event wait one */
		if(num < 1) {
			if(WaitForSingleObject(hStdIn, INFINITE) != WAIT_OBJECT_0) {
				LOG_ERROR("WaitForSingleObject failed (error %lu)", GetLastError());
				return input;
			}
		}

		if(!PeekConsoleInput(hStdIn, &event, 1, &num)) {
			LOG_ERROR("PeekConsoleInput failed (error %lu)", GetLastError());
			return input;
		}
		if(num < 1) {
			LOG_ERROR("WaitForSingleObject returned without an input event");
			return input;
		}
	}

	/* Compare the processed inputs counter for the case when the event is repeated (key old down) */
	if(event.Event.KeyEvent.wRepeatCount - processedInputsNb > 1) {
		//Increment the number of inputs processed for this event
		++processedInputsNb;
	}
	else {
		//All inputs are processed
		//Remove the event from the console input buffer
		if(!ReadConsoleInput(hStdIn, &event, 1, &num)) {
			LOG_ERROR("ReadConsoleInput failed (error %lu)", GetLastError());
			return input;
		}
		processedInputsNb = 0;
	}

	switch(event.Event.KeyEvent.wVirtualKeyCode) {
		case VK_HOME:
			input.key = HOME_KEY;
			break;
		case VK_END:
			input.key = END_KEY;
			break;
		case VK_PRIOR:
			input.key = PAGE_UP_KEY;
			break;
		case VK_NEXT:
			input.key = PAGE_DOWN_KEY;
			break;
		case VK_UP:
			input.key = UP_ARROW_KEY;
			break;
		case VK_DOWN:
			input.key = DOWN_ARROW_KEY;
			break;
		case VK_LEFT:
			input.key = LEFT_ARROW_KEY;
			break;
		case VK_RIGHT:
			input.key = RIGHT_ARROW_KEY;
			break;
		case VK_BACK:
			input.key = BACKSPACE_KEY;
			break;
		case VK_TAB:
			input.key = TAB_KEY;
			break;
		case VK_RETURN:
			input.key = ENTER_KEY;
			break;
		case VK_ESCAPE:
			input.key = ESC_KEY;
			break;
		case VK_SPACE:
			input.key = SPACE_KEY;
			break;
		case VK_INSERT:
			input.key = INS_KEY;
			break;
		case VK_DELETE:
			input.key = DEL_KEY;
			break;
		case VK_F1:
			input.key = F1_KEY;
			break;
		case VK_F2:
			input.key = F2_KEY;
			break;
		case VK_F3:
			input.key = F3_KEY;
			break;
		case VK_F4:
			input.key = F4_KEY;
			break;
		case VK_F5:
			input.key = F5_KEY;
			break;
		case VK_F6:
			input.key = F6_KEY;
			break;
		case VK_F7:
			input.key = F7_KEY;
			break;
		case VK_F8:
			input.key = F8_KEY;
			break;
		case VK_F9:
			input.key = F9_KEY;
			break;
		case VK_F10:
			input.key = F10_KEY;
			break;
		case VK_F11:
			input.key = F11_KEY;
			break;
		case VK_F12:
			input.key = F12_KEY;
			break;
		default:
			break;
	}

	if(input.key == OTHER_KEY) {
		input.ch = event.Event.KeyEvent.uChar.AsciiChar;
	}
	else {
		input.ch = cc_getAssociatedChar(input.key);
	}

	return input;
}

// functions from WindowsConsoleControl.h

cc_Vector2 cc_getCursorPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		cc_Vector2 position = {0, 0};
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		cc_Vector2 position = {0, 0};
		return position;
	}

	cc_Vector2 position = {
		csbi.dwCursorPosition.X - csbi.srWindow.Left,
		csbi.dwCursorPosition.Y - csbi.srWindow.Top
	};
	return position;
}

cc_Vector2 cc_getCursorGlobalPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		cc_Vector2 position = {0, 0};
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		cc_Vector2 position = {0, 0};
		return position;
	}

	cc_Vector2 position = {
		csbi.dwCursorPosition.X,
		csbi.dwCursorPosition.Y
	};
	return position;
}

void cc_reverseColors() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut, csbi.wAttributes | (WORD) COMMON_LVB_REVERSE_VIDEO)) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

cc_type cc_getGlobalWidth() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.dwSize.X;
}

cc_type cc_getGlobalHeight() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.dwSize.Y;
}

void cc_setCursorGlobalPosition(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	COORD pos = {
		(short) position.x,
		(short) position.y
	};
	if(!SetConsoleCursorPosition(hStdOut, pos)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

cc_Vector2 cc_globalClamp(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return position;
	}

	short maxX = (short) (csbi.dwSize.X - 1);
	short maxY = (short) (csbi.dwSize.Y - 1);
	cc_Vector2 result = {
		position.x < maxX ? (position.x < 0 ? 0 : position.x) : maxX,
		position.y < maxY ? (position.y < 0 ? 0 : position.y) : maxY
	};
	return result;
}

bool cc_globalContains(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return false;
	}

	return position.x >= 0
	       && position.y >= 0
	       && position.x < csbi.dwSize.X
	       && position.y < csbi.dwSize.Y;
}

void cc_setCursorSize(unsigned int size) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_CURSOR_INFO cci;
	if(!GetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERROR("GetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}

	if(size < 100) {
		cci.dwSize = size;
	}
	else {
		cci.dwSize = 100;
	}

	if(!SetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERROR("SetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}
}

#endif //_WIN32
