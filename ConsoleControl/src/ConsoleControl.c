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

#ifdef OS_WINDOWS

// For cc_saveCursorPosition and cc_restoreCursorPosition
static cc_Vector2 savedPosition = {0, 0};

static WORD cc_getForegroundColorIdentifier(cc_Color color);

static WORD cc_getBackgroundColorIdentifier(cc_Color color);

WORD cc_getForegroundColorIdentifier(cc_Color color) {
	WORD colorIdentifier = 0;
	switch(color) {
		case LIGHT_BLUE:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case BLUE:
			colorIdentifier |= FOREGROUND_BLUE;
			break;
		case LIGHT_GREEN:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case GREEN:
			colorIdentifier |= FOREGROUND_GREEN;
			break;
		case LIGHT_CYAN:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CYAN:
			colorIdentifier |= FOREGROUND_BLUE | FOREGROUND_GREEN;
			break;
		case LIGHT_RED:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case RED:
			colorIdentifier |= FOREGROUND_RED;
			break;
		case LIGHT_MAGENTA:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case MAGENTA:
			colorIdentifier |= FOREGROUND_BLUE | FOREGROUND_RED;
			break;
		case LIGHT_YELLOW:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case YELLOW:
			colorIdentifier |= FOREGROUND_GREEN | FOREGROUND_RED;
			break;
		case LIGHT_WHITE:
			colorIdentifier |= FOREGROUND_INTENSITY;
			/* FALLTHROUGH */
		case WHITE:
			colorIdentifier |= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
			break;
		case LIGHT_BLACK:
			colorIdentifier |= FOREGROUND_INTENSITY;
			break;
		case BLACK:
			/* FALLTHROUGH */
		default:
			break;
	}
	return colorIdentifier;
}

WORD cc_getBackgroundColorIdentifier(cc_Color color) {
	WORD colorIdentifier = 0;
	switch(color) {
		case LIGHT_BLUE:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case BLUE:
			colorIdentifier |= BACKGROUND_BLUE;
			break;
		case LIGHT_GREEN:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case GREEN:
			colorIdentifier |= BACKGROUND_GREEN;
			break;
		case LIGHT_CYAN:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case CYAN:
			colorIdentifier |= BACKGROUND_BLUE | BACKGROUND_GREEN;
			break;
		case LIGHT_RED:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case RED:
			colorIdentifier |= BACKGROUND_RED;
			break;
		case LIGHT_MAGENTA:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case MAGENTA:
			colorIdentifier |= BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case LIGHT_YELLOW:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case YELLOW:
			colorIdentifier |= BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case LIGHT_WHITE:
			colorIdentifier |= BACKGROUND_INTENSITY;
			/* FALLTHROUGH */
		case WHITE:
			colorIdentifier |= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case LIGHT_BLACK:
			colorIdentifier |= BACKGROUND_INTENSITY;
			break;
		case BLACK:
			/* FALLTHROUGH */
		default:
			break;
	}
	return colorIdentifier;
}

void cc_setForegroundColor(const cc_Color color) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut,
	                            (csbi.wAttributes /* current colors */
	                             & cc_getBackgroundColorIdentifier(LIGHT_WHITE)) /* only keep background */
	                            | cc_getForegroundColorIdentifier(color)) /* change foreground */) {
		LOG_ERR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setBackgroundColor(const cc_Color color) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut,
	                            (csbi.wAttributes /* current colors */
	                             & cc_getForegroundColorIdentifier(LIGHT_WHITE)) /* only keep foreground */
	                            | cc_getBackgroundColorIdentifier(color)) /* change background */) {
		LOG_ERR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setColors(const cc_Color backgroundColor, const cc_Color foregroundColor) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut,
	                            cc_getBackgroundColorIdentifier(backgroundColor)
	                            | cc_getForegroundColorIdentifier(foregroundColor))) {
		LOG_ERR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

cc_type cc_getWidth() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

cc_type cc_getHeight() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void cc_setCursorPosition(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD pos = {
		(short) (position.x + csbi.srWindow.Left),
		(short) (position.y + csbi.srWindow.Top)
	};

	if(!SetConsoleCursorPosition(hStdOut, pos)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorUp(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y - steps)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorDown(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y + steps)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorLeft(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X - steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorRight(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorHorizontally(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorVertically(cc_type steps) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y + steps)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursor(cc_Vector2 move) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + move.x),
		(SHORT) (csbi.dwCursorPosition.Y + move.y)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_saveCursorPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	savedPosition.x = csbi.dwCursorPosition.X - csbi.srWindow.Left;
	savedPosition.y = csbi.dwCursorPosition.Y - csbi.srWindow.Top;
}

void cc_restoreCursorPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(short) (savedPosition.x + csbi.srWindow.Left),
		(short) (savedPosition.y + csbi.srWindow.Top)
	};

	if(!SetConsoleCursorPosition(hStdOut, position)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setCursorVisibility(bool visibility) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_CURSOR_INFO cci;
	if(!GetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERR("GetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}

	if(visibility) {
		cci.bVisible = TRUE;
	}
	else {
		cci.bVisible = FALSE;
	}

	if(!SetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERR("SetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}
}

cc_Vector2 cc_clamp(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
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
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return x;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return x;
	}

	short maxX = (short) (csbi.srWindow.Right - csbi.srWindow.Left);
	return x < maxX ? (x < 0 ? 0 : x) : maxX;
}

cc_type cc_clampY(cc_type y) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return y;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return y;
	}

	short maxY = (short) (csbi.srWindow.Bottom - csbi.srWindow.Top - 1);
	return y < maxY ? (y < 0 ? 0 : y) : maxY;
}

bool cc_contains(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
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
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
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
		LOG_ERR("FillConsoleOutputCharacter failed (error %lu)", GetLastError());
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
		LOG_ERR("FillConsoleOutputAttribute failed (error %lu)", GetLastError());
		return;
	}

	/* Move the cursor home */
	if(!SetConsoleCursorPosition(hStdOut, homeCoords)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
	}
}

// credits: http://www.cplusplus.com/articles/4z18T05o/
void cc_completeClean() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	/* Get the number of cells in the current buffer */
	DWORD cellCount = (DWORD) (csbi.dwSize.X * csbi.dwSize.Y);

	COORD homeCoords = {0, 0};
	DWORD count;

	/* Fill the entire buffer with spaces */
	if(!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) {
		LOG_ERR("FillConsoleOutputCharacter failed (error %lu)", GetLastError());
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
		LOG_ERR("FillConsoleOutputAttribute failed (error %lu)", GetLastError());
		return;
	}

	/* Move the cursor home */
	if(!SetConsoleCursorPosition(hStdOut, homeCoords)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
	}
}

char cc_instantGetChar() {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return 0;
	}

	/* Save console mode */
	DWORD saveMode;
	if(!GetConsoleMode(hStdIn, &saveMode)) {
		LOG_ERR("GetConsoleMode failed (error %lu)", GetLastError());
		return 0;
	}
	if(!SetConsoleMode(hStdIn, ENABLE_PROCESSED_INPUT)) {
		LOG_ERR("SetConsoleMode failed (error %lu)", GetLastError());
		return 0;
	}

	TCHAR ch = 0;
	if(WaitForSingleObject(hStdIn, INFINITE) == WAIT_OBJECT_0) {
		DWORD num;
		if(!ReadConsole(hStdIn, &ch, 1, &num, NULL)) {
			LOG_ERR("ReadConsole failed (error %lu)", GetLastError());
		}
		if(num != 1) {
			SLOG_ERR("Bad characters read number");
		}
	}
	else {
		LOG_ERR("WaitForSingleObject failed (error %lu)", GetLastError());
	}

	/* Restore console mode */
	if(!SetConsoleMode(hStdIn, saveMode)) {
		LOG_ERR("SetConsoleMode failed (error %lu)", GetLastError());
	}
	return ch;
}

bool cc_waitingInput() {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return false;
	}

	DWORD num;
	if(!GetNumberOfConsoleInputEvents(hStdIn, &num)) {
		LOG_ERR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
		return false;
	}

	return (num > 1);
}

void cc_displayInputs(bool display) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	/* Get console mode */
	DWORD mode;
	if(!GetConsoleMode(hStdIn, &mode)) {
		LOG_ERR("GetConsoleMode failed (error %lu)", GetLastError());
		return;
	}

	if(display) {
		/* Add echo input to the mode */
		if(!SetConsoleMode(hStdIn, mode | ENABLE_ECHO_INPUT)) {
			LOG_ERR("SetConsoleMode failed (error %lu)", GetLastError());
			return;
		}
	}
	else {
		/* Remove echo input to the mode */
		if(!SetConsoleMode(hStdIn, mode & ~((DWORD) ENABLE_ECHO_INPUT))) {
			LOG_ERR("SetConsoleMode failed (error %lu)", GetLastError());
			return;
		}
	}
}

static WORD processedInputsNb = 0;

cc_Input cc_getInput() {
	cc_Input input = {OTHER_KEY, 0};

	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return input;
	}
	DWORD num;

	/* Get number of input event */
	if(!GetNumberOfConsoleInputEvents(hStdIn, &num)) {
		LOG_ERR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
		return input;
	}

	/* If there is no input event wait one */
	if(num < 1) {
		if(WaitForSingleObject(hStdIn, INFINITE) != WAIT_OBJECT_0) {
			LOG_ERR("WaitForSingleObject failed (error %lu)", GetLastError());
			return input;
		}
	}

	/* Read the first event that is a key pressed event */
	INPUT_RECORD event;
	if(!PeekConsoleInput(hStdIn, &event, 1, &num)) {
		LOG_ERR("PeekConsoleInput failed (error %lu)", GetLastError());
		return input;
	}
	if(num < 1) {
		SLOG_ERR("WaitForSingleObject returned without an input event");
		return input;
	}
	while(event.EventType != KEY_EVENT || !event.Event.KeyEvent.bKeyDown) {
		/* Not a key pressed event, remove it from the console input buffer */
		if(!ReadConsoleInput(hStdIn, &event, 1, &num)) {
			LOG_ERR("ReadConsoleInput failed (error %lu)", GetLastError());
			return input;
		}

		/* Get number of input event */
		if(!GetNumberOfConsoleInputEvents(hStdIn, &num)) {
			LOG_ERR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
			return input;
		}

		/* If there is no input event wait one */
		if(num < 1) {
			if(WaitForSingleObject(hStdIn, INFINITE) != WAIT_OBJECT_0) {
				LOG_ERR("WaitForSingleObject failed (error %lu)", GetLastError());
				return input;
			}
		}

		if(!PeekConsoleInput(hStdIn, &event, 1, &num)) {
			LOG_ERR("PeekConsoleInput failed (error %lu)", GetLastError());
			return input;
		}
		if(num < 1) {
			SLOG_ERR("WaitForSingleObject returned without an input event");
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
			LOG_ERR("ReadConsoleInput failed (error %lu)", GetLastError());
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

#else //OS_WINDOWS

#define _KEYS_DEF_SEC_LENGTH 5

#define KEYS_DEFINITIONS_TABLE(ENTRY)         \
        ENTRY(HOME_KEY, 27, 91, 72)           \
        ENTRY(HOME_KEY, 27, 91, 49, 126)      \
        ENTRY(END_KEY, 27, 91, 70)            \
        ENTRY(END_KEY, 27, 91, 52, 126)       \
        ENTRY(PAGE_UP_KEY, 27, 91, 53, 126)   \
        ENTRY(PAGE_DOWN_KEY, 27, 91, 54, 126) \
        ENTRY(UP_ARROW_KEY, 27, 91, 65)       \
        ENTRY(DOWN_ARROW_KEY, 27, 91, 66)     \
        ENTRY(LEFT_ARROW_KEY, 27, 91, 68)     \
        ENTRY(RIGHT_ARROW_KEY, 27, 91, 67)    \
        ENTRY(BACKSPACE_KEY, 8)               \
        ENTRY(TAB_KEY, 9)                     \
        ENTRY(ENTER_KEY, 10)                  \
        ENTRY(ENTER_KEY, 13)                  \
        ENTRY(ESC_KEY, 27)                    \
        ENTRY(SPACE_KEY, 32)                  \
        ENTRY(INS_KEY, 27, 91, 50, 126)       \
        ENTRY(DEL_KEY, 27, 91, 51, 126)       \
        ENTRY(F1_KEY, 27, 79, 80)             \
        ENTRY(F1_KEY, 27, 91, 91, 65)         \
        ENTRY(F1_KEY, 27, 91, 49, 49, 126)    \
        ENTRY(F2_KEY, 27, 79, 81)             \
        ENTRY(F2_KEY, 27, 91, 91, 66)         \
        ENTRY(F2_KEY, 27, 91, 49, 50, 126)    \
        ENTRY(F3_KEY, 27, 79, 82)             \
        ENTRY(F3_KEY, 27, 91, 91, 67)         \
        ENTRY(F3_KEY, 27, 91, 49, 51, 126)    \
        ENTRY(F4_KEY, 27, 79, 83)             \
        ENTRY(F4_KEY, 27, 91, 91, 68)         \
        ENTRY(F4_KEY, 27, 91, 49, 52, 126)    \
        ENTRY(F5_KEY, 27, 91, 91, 69)         \
        ENTRY(F5_KEY, 27, 91, 49, 53, 126)    \
        ENTRY(F6_KEY, 27, 91, 49, 55, 126)    \
        ENTRY(F7_KEY, 27, 91, 49, 56, 126)    \
        ENTRY(F8_KEY, 27, 91, 49, 57, 126)    \
        ENTRY(F9_KEY, 27, 91, 50, 48, 126)    \
        ENTRY(F10_KEY, 27, 91, 50, 49, 126)   \
        ENTRY(F11_KEY, 27, 91, 50, 51, 126)   \
        ENTRY(F12_KEY, 27, 91, 50, 52, 126)   \

#define _EXPAND_AS_SEQUENCE(key, ...) {__VA_ARGS__},
#define _EXPAND_AS_KEY(key, ...) key,

static char keysDefinitionSequences[][_KEYS_DEF_SEC_LENGTH] = {
	KEYS_DEFINITIONS_TABLE(_EXPAND_AS_SEQUENCE)
};

static cc_Key keysDefinition[] = {
	KEYS_DEFINITIONS_TABLE(_EXPAND_AS_KEY)
};

//if match, return true, key is the match
//if no mach but input start a match, return true, key is OTHER_KEY
//if no mach, return false, key is OTHER_KEY
bool cc_matchKeyDefinition(char* input, cc_Key* key);

static const char* cc_getForegroundColorIdentifier(cc_Color color);

static const char* cc_getBackgroundColorIdentifier(cc_Color color);

bool cc_matchKeyDefinition(char* input, cc_Key* key) {
	bool canMatch = false;
	unsigned int keysDefinitionSequencesNumber = (sizeof(keysDefinitionSequences)
	                                              / _KEYS_DEF_SEC_LENGTH
	                                              * sizeof(char));
	for(unsigned int i = 0; i < keysDefinitionSequencesNumber; ++i) {
		unsigned int j = 0;
		while(j < _KEYS_DEF_SEC_LENGTH && input[j] != 0 && keysDefinitionSequences[i][j] == input[j]) {
			++j;
		}
		if(j == _KEYS_DEF_SEC_LENGTH
		   || keysDefinitionSequences[i][j] == input[j]) { // both == 0
			*key = keysDefinition[i];
			return true;
		}
		if(input[j] == 0) { // && keysDefinitionSequences[i][j] != 0
			canMatch = true;
		}
	}
	return canMatch;
}

const char* cc_getForegroundColorIdentifier(cc_Color color) {
	switch(color) {
		case BLACK:
			return "30";
		case RED:
			return "31";
		case GREEN:
			return "32";
		case YELLOW:
			return "33";
		case BLUE:
			return "34";
		case MAGENTA:
			return "35";
		case CYAN:
			return "36";
		case WHITE:
			return "37";
		case LIGHT_BLACK:
			return "90";
		case LIGHT_RED:
			return "91";
		case LIGHT_GREEN:
			return "92";
		case LIGHT_YELLOW:
			return "93";
		case LIGHT_BLUE:
			return "94";
		case LIGHT_MAGENTA:
			return "95";
		case LIGHT_CYAN:
			return "96";
		case LIGHT_WHITE:
			return "97";
		default:
			return "37"; //WHITE
	}
}

const char* cc_getBackgroundColorIdentifier(cc_Color color) {
	switch(color) {
		case BLACK:
			return "40";
		case RED:
			return "41";
		case GREEN:
			return "42";
		case YELLOW:
			return "43";
		case BLUE:
			return "44";
		case MAGENTA:
			return "45";
		case CYAN:
			return "46";
		case WHITE:
			return "47";
		case LIGHT_BLACK:
			return "100";
		case LIGHT_RED:
			return "101";
		case LIGHT_GREEN:
			return "102";
		case LIGHT_YELLOW:
			return "103";
		case LIGHT_BLUE:
			return "104";
		case LIGHT_MAGENTA:
			return "105";
		case LIGHT_CYAN:
			return "106";
		case LIGHT_WHITE:
			return "107";
		default:
			return "40"; //BLACK
	}
}

void cc_setForegroundColor(cc_Color color) {
	printf(CSI "%s" SGR_CODE, cc_getForegroundColorIdentifier(color));
}

void cc_setBackgroundColor(cc_Color color) {
	printf(CSI "%s" SGR_CODE, cc_getBackgroundColorIdentifier(color));
}

void cc_setColors(cc_Color backgroundColor, cc_Color foregroundColor) {
	printf(CSI "%s" SGR_CODE, cc_getBackgroundColorIdentifier(backgroundColor));
	printf(CSI "%s" SGR_CODE, cc_getForegroundColorIdentifier(foregroundColor));
}

cc_type cc_getWidth() {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		SLOG_ERR("ioctl failed");
		return 0;
	}

	return w.ws_col;
}

cc_type cc_getHeight() {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		SLOG_ERR("ioctl failed");
		return 0;
	}

	return w.ws_row;
}

void cc_setCursorPosition(cc_Vector2 position) {
	printf(CSI "%d;%d" CUP_CODE, position.y + 1, position.x + 1);
}

void cc_moveCursorUp(cc_type steps) {
	if(steps > 0) {
		printf(CSI "%d" CUU_CODE, steps);
	}
	else if(steps < 0) {
		printf(CSI "%d" CUD_CODE, -steps);
	}
}

void cc_moveCursorDown(cc_type steps) {
	if(steps > 0) {
		printf(CSI "%d" CUD_CODE, steps);
	}
	else if(steps < 0) {
		printf(CSI "%d" CUU_CODE, -steps);
	}
}

void cc_moveCursorLeft(cc_type steps) {
	if(steps > 0) {
		printf(CSI "%d" CUB_CODE, steps);
	}
	else if(steps < 0) {
		printf(CSI "%d" CUF_CODE, -steps);
	}
}

void cc_moveCursorRight(cc_type steps) {
	if(steps > 0) {
		printf(CSI "%d" CUF_CODE, steps);
	}
	else if(steps < 0) {
		printf(CSI "%d" CUB_CODE, -steps);
	}
}

void cc_moveCursorHorizontally(cc_type steps) {
	if(steps > 0) {
		printf(CSI "%d" CUF_CODE, steps);
	}
	else if(steps < 0) {
		printf(CSI "%d" CUB_CODE, -steps);
	}
}

void cc_moveCursorVertically(cc_type steps) {
	if(steps > 0) {
		printf(CSI "%d" CUD_CODE, steps);
	}
	else if(steps < 0) {
		printf(CSI "%d" CUU_CODE, -steps);
	}
}

void cc_moveCursor(cc_Vector2 move) {
	cc_moveCursorHorizontally(move.x);
	cc_moveCursorVertically(move.y);
}

void cc_saveCursorPosition() {
	printf(CSI SCP_CODE);
}

void cc_restoreCursorPosition() {
	printf(CSI RCP_CODE);
}

void cc_setCursorVisibility(bool visibility) {
	if(visibility) {
		printf(CSI DECTCEM_S_CODE);
	}
	else {
		printf(CSI DECTCEM_H_CODE);
	}
}

cc_Vector2 cc_clamp(cc_Vector2 position) {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		SLOG_ERR("ioctl failed");
		return position;
	}

	cc_type maxX = w.ws_col - 1;
	cc_type maxY = w.ws_row - 1;
	cc_Vector2 result = {
		position.x < maxX ? (position.x < 0 ? 0 : position.x) : maxX,
		position.y < maxY ? (position.y < 0 ? 0 : position.y) : maxY
	};
	return result;
}

cc_type cc_clampX(cc_type x) {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		SLOG_ERR("ioctl failed");
		return x;
	}

	cc_type maxX = w.ws_col - 1;
	return x < maxX ? (x < 0 ? 0 : x) : maxX;
}

cc_type cc_clampY(cc_type y) {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		SLOG_ERR("ioctl failed");
		return y;
	}

	cc_type maxY = w.ws_row - 1;
	return y < maxY ? (y < 0 ? 0 : y) : maxY;
}

bool cc_contains(cc_Vector2 position) {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		SLOG_ERR("ioctl failed");
		return false;
	}

	return position.x >= 0
	       && position.y >= 0
	       && position.x < w.ws_col
	       && position.y < w.ws_row;
}

void cc_clean() {
	printf(CSI "2" ED_CODE);
	printf(CSI "0;0" CUP_CODE);
}

void cc_completeClean() {
	printf(CSI "2" ED_CODE);
	printf(CSI "3" ED_CODE);
	printf(CSI "0;0" CUP_CODE);
}

char cc_instantGetChar() {
	struct termios oldt, newt;
	char ch;

	/* Save console mode */
	errno = 0;
	if(tcgetattr(STDIN_FILENO, &oldt)) {
		LOG_ERR("tcgetattr failed (%s)", strerror(errno));
		return 0;
	}

	/* Set console mode to non canonical (return without waiting '\n') */
	newt = oldt;
	newt.c_lflag &= ~((tcflag_t) ICANON);        // non canonical
	newt.c_cc[VMIN] = 1;                         // read only 1 character
	newt.c_cc[VTIME] = 0;                        // forever wait for an input
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &newt)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		return 0;
	}

	/* Wait and take first stdin char */
	ch = (char) getchar();

	/* Restore console mode */
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &oldt)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		return 0;
	}

	return ch;
}

bool cc_waitingInput() {
	struct termios oldt, newt;
	int ch;
	int oldf;

	/* Save console mode */
	errno = 0;
	if(tcgetattr(STDIN_FILENO, &oldt)) {
		LOG_ERR("tcgetattr failed (%s)", strerror(errno));
		return false;
	}

	/* Set console mode to non canonical (return without waiting '\n') and no echo */
	newt = oldt;
	newt.c_lflag &= ~((tcflag_t)(ICANON | ECHO));
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &newt)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		return false;
	}

	/* Save stdin file status flags */
	errno = 0;
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	if(errno) {
		LOG_ERR("fcntl failed (%s)", strerror(errno));
		return false;
	}

	/* Add non blocking to file status flags, to avoid waiting user input if stdin is empty */
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	if(errno) {
		LOG_ERR("fcntl failed (%s)", strerror(errno));
		return false;
	}

	/* Take first stdin char */
	ch = getchar();

	/* Restore console mode */
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &oldt)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		return false;
	}

	/* Restore stdin file status flags */
	errno = 0;
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if(errno) {
		LOG_ERR("fcntl failed (%s)", strerror(errno));
		return false;
	}

	/* Check if stdin was empty */
	if(ch != EOF) {
		errno = 0;
		/* Put back the taken char */
		if(ungetc(ch, stdin) == EOF) {
			LOG_ERR("ungetc failed (%s)", strerror(errno));
			return false;
		}
		return true;
	}

	return false;
}

void cc_displayInputs(bool display) {
	struct termios t;

	/* Get console mode */
	errno = 0;
	if(tcgetattr(STDIN_FILENO, &t)) {
		LOG_ERR("tcgetattr failed (%s)", strerror(errno));
		return;
	}

	/* Set console mode to display or no echo */
	if(display) {
		t.c_lflag |= ECHO;
	}
	else {
		t.c_lflag &= ~((tcflag_t) ECHO);
	}
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &t)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		return;
	}
}

cc_Input cc_getInput() {
	cc_Input input = {OTHER_KEY, 0};

	struct termios oldt, newt;
	char lastch;
	char* inputChar = (char*) calloc(_KEYS_DEF_SEC_LENGTH, sizeof(char));
	unsigned char chNumber = 0;
	cc_Key matchedKey = OTHER_KEY;
	unsigned int matchpos = 1; // at least just a char

	/* Save console mode */
	errno = 0;
	if(tcgetattr(STDIN_FILENO, &oldt)) {
		LOG_ERR("tcgetattr failed (%s)", strerror(errno));
		free(inputChar);
		return input;
	}

	/* Set console mode to non canonical (return without waiting '\n') */
	newt = oldt;
	newt.c_lflag &= ~((tcflag_t) ICANON);        // non canonical
	newt.c_cc[VMIN] = 1;                         // read only 1 character
	newt.c_cc[VTIME] = 0;                        // forever wait for an input
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &newt)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		free(inputChar);
		return input;
	}

	/* Determine the input */
	lastch = (char) getchar();
	inputChar[chNumber++] = lastch;
	while(cc_matchKeyDefinition(inputChar, &matchedKey) && cc_waitingInput()) {
		if(matchedKey != OTHER_KEY) {
			input.key = matchedKey;
			matchpos = chNumber;
			matchedKey = OTHER_KEY;
		}
		lastch = (char) getchar();
		inputChar[chNumber++] = lastch;
	}
	if(matchedKey != OTHER_KEY) {
		input.key = matchedKey;
		matchpos = chNumber;
	}

	/* Put back the non matched chars */
	while(chNumber > matchpos) {
		if(ungetc(inputChar[--chNumber], stdin) == EOF) {
			LOG_ERR("ungetc failed (%s)", strerror(errno));
			free(inputChar);
			return input;
		}
	}

	if(input.key == OTHER_KEY) {
		/* Set the last taken char as ch */
		input.ch = inputChar[--chNumber];
	}
	else {
		input.ch = cc_getAssociatedChar(input.key);
	}

	/* Restore console mode */
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &oldt)) {
		LOG_ERR("tcsetattr failed (%s)", strerror(errno));
		free(inputChar);
		return input;
	}

	free(inputChar);
	return input;
}

#endif //OS_WINDOWS

void cc_printInPlace(const char c) {
	printf("%c\b", c);
}

char cc_getAssociatedChar(cc_Key key) {
	switch(key) {
		case BACKSPACE_KEY:
			return 8;
		case TAB_KEY:
			return 9;
		case ENTER_KEY:
			return 13;
		case ESC_KEY:
			return 27;
		case SPACE_KEY:
			return 32;
		case HOME_KEY:
			/* FALLTHROUGH */
		case END_KEY:
			/* FALLTHROUGH */
		case PAGE_UP_KEY:
			/* FALLTHROUGH */
		case PAGE_DOWN_KEY:
			/* FALLTHROUGH */
		case UP_ARROW_KEY:
			/* FALLTHROUGH */
		case DOWN_ARROW_KEY:
			/* FALLTHROUGH */
		case LEFT_ARROW_KEY:
			/* FALLTHROUGH */
		case RIGHT_ARROW_KEY:
			/* FALLTHROUGH */
		case INS_KEY:
			/* FALLTHROUGH */
		case DEL_KEY:
			/* FALLTHROUGH */
		case F1_KEY:
			/* FALLTHROUGH */
		case F2_KEY:
			/* FALLTHROUGH */
		case F3_KEY:
			/* FALLTHROUGH */
		case F4_KEY:
			/* FALLTHROUGH */
		case F5_KEY:
			/* FALLTHROUGH */
		case F6_KEY:
			/* FALLTHROUGH */
		case F7_KEY:
			/* FALLTHROUGH */
		case F8_KEY:
			/* FALLTHROUGH */
		case F9_KEY:
			/* FALLTHROUGH */
		case F10_KEY:
			/* FALLTHROUGH */
		case F11_KEY:
			/* FALLTHROUGH */
		case F12_KEY:
			/* FALLTHROUGH */
		case OTHER_KEY:
			/* FALLTHROUGH */
		default:
			break;
	}
	return 0;
}
