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

#include <definitions/ConsoleControlColor.h>
#include <definitions/ConsoleControlInput.h>
#include <log.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <windows.h>

#define UNUSED_PARAMETER(x) (void)(x)

typedef struct {
	HANDLE hStdIn;
	HANDLE hStdOut;
} cc_Context;

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

cc_Handle cc_start() {
	cc_Context* ccc = (cc_Context*) malloc(sizeof(cc_Context));

	ccc->hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if(ccc->hStdIn == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		free(ccc);
		return NULL;
	}

	ccc->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(ccc->hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERROR("GetStdHandle failed (error %lu)", GetLastError());
		free(ccc);
		return NULL;
	}

	return ccc;
}

void cc_end(cc_Handle cch) {
	if(cch != NULL)
		free(cch);
}

void cc_setForegroundColor(cc_Handle cch, const cc_Color color) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(ccc->hStdOut,
	                            (csbi.wAttributes /* current colors */
	                             & cc_getBackgroundColorIdentifier(CC_LIGHT_WHITE)) /* only keep background */
	                            | cc_getForegroundColorIdentifier(color)) /* change foreground */) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setBackgroundColor(cc_Handle cch, const cc_Color color) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(ccc->hStdOut,
	                            (csbi.wAttributes /* current colors */
	                             & cc_getForegroundColorIdentifier(CC_LIGHT_WHITE)) /* only keep foreground */
	                            | cc_getBackgroundColorIdentifier(color)) /* change background */) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setColors(cc_Handle cch, const cc_Color backgroundColor, const cc_Color foregroundColor) {
	cc_Context* ccc = (cc_Context*) cch;

	if(!SetConsoleTextAttribute(ccc->hStdOut,
	                            cc_getBackgroundColorIdentifier(backgroundColor)
	                            | cc_getForegroundColorIdentifier(foregroundColor))) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

int cc_getWidth(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int cc_getHeight(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void cc_setCursorPosition(cc_Handle cch, const cc_Vector2 position) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD pos = {
		(SHORT) (position.x + csbi.srWindow.Left),
		(SHORT) (position.y + csbi.srWindow.Top)
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, pos)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorUp(cc_Handle cch, int steps) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y - steps)
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorDown(cc_Handle cch, int steps) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y + steps)
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorLeft(cc_Handle cch, int steps) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X - steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorRight(cc_Handle cch, int steps) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorHorizontally(cc_Handle cch, int steps) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + steps),
		csbi.dwCursorPosition.Y
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursorVertically(cc_Handle cch, int steps) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		csbi.dwCursorPosition.X,
		(SHORT) (csbi.dwCursorPosition.Y + steps)
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_moveCursor(cc_Handle cch, cc_Vector2 move) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (csbi.dwCursorPosition.X + move.x),
		(SHORT) (csbi.dwCursorPosition.Y + move.y)
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_saveCursorPosition(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	savedPosition.x = csbi.dwCursorPosition.X - csbi.srWindow.Left;
	savedPosition.y = csbi.dwCursorPosition.Y - csbi.srWindow.Top;
}

void cc_restoreCursorPosition(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	COORD position = {
		(SHORT) (savedPosition.x + csbi.srWindow.Left),
		(SHORT) (savedPosition.y + csbi.srWindow.Top)
	};

	if(!SetConsoleCursorPosition(ccc->hStdOut, position)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

void cc_setCursorVisibility(cc_Handle cch, bool visibility) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_CURSOR_INFO cci;
	if(!GetConsoleCursorInfo(ccc->hStdOut, &cci)) {
		LOG_ERROR("GetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}

	if(visibility) {
		cci.bVisible = TRUE;
	}
	else {
		cci.bVisible = FALSE;
	}

	if(!SetConsoleCursorInfo(ccc->hStdOut, &cci)) {
		LOG_ERROR("SetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}
}

cc_Vector2 cc_clamp(cc_Handle cch, const cc_Vector2 position) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return position;
	}

	int maxX = csbi.srWindow.Right - csbi.srWindow.Left;
	int maxY = csbi.srWindow.Bottom - csbi.srWindow.Top;
	cc_Vector2 result = {
		position.x < maxX ? (position.x < 0 ? 0 : position.x) : maxX,
		position.y < maxY ? (position.y < 0 ? 0 : position.y) : maxY
	};
	return result;
}

int cc_clampX(cc_Handle cch, int x) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return x;
	}

	int maxX = csbi.srWindow.Right - csbi.srWindow.Left;
	return x < maxX ? (x < 0 ? 0 : x) : maxX;
}

int cc_clampY(cc_Handle cch, int y) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return y;
	}

	int maxY = csbi.srWindow.Bottom - csbi.srWindow.Top - 1;
	return y < maxY ? (y < 0 ? 0 : y) : maxY;
}

bool cc_contains(cc_Handle cch, const cc_Vector2 position) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return false;
	}

	return position.x >= 0
	       && position.y >= 0
	       && position.x <= (csbi.srWindow.Right - csbi.srWindow.Left)
	       && position.y <= (csbi.srWindow.Bottom - csbi.srWindow.Top);
}

// credits: http://www.cplusplus.com/articles/4z18T05o/
void cc_clean(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	/* Compute the number of cells in the current screen */
	DWORD cellCount = (DWORD) ((csbi.srWindow.Right - csbi.srWindow.Left + 1)
	                           * (csbi.srWindow.Bottom - csbi.srWindow.Top + 1));

	/* Home is at the top left of the current screen */
	COORD homeCoords = {csbi.srWindow.Left, csbi.srWindow.Top};
	DWORD count;

	/* Fill the entire buffer with spaces */
	if(!FillConsoleOutputCharacter(ccc->hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputCharacter failed (error %lu)", GetLastError());
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if(!FillConsoleOutputAttribute(ccc->hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputAttribute failed (error %lu)", GetLastError());
		return;
	}

	/* Move the cursor home */
	if(!SetConsoleCursorPosition(ccc->hStdOut, homeCoords)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
	}
}

// credits: http://www.cplusplus.com/articles/4z18T05o/
void cc_completeClean(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	/* Get the number of cells in the current buffer */
	DWORD cellCount = (DWORD) (csbi.dwSize.X * csbi.dwSize.Y);

	COORD homeCoords = {0, 0};
	DWORD count;

	/* Fill the entire buffer with spaces */
	if(!FillConsoleOutputCharacter(ccc->hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputCharacter failed (error %lu)", GetLastError());
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if(!FillConsoleOutputAttribute(ccc->hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
		LOG_ERROR("FillConsoleOutputAttribute failed (error %lu)", GetLastError());
		return;
	}

	/* Move the cursor home */
	if(!SetConsoleCursorPosition(ccc->hStdOut, homeCoords)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
	}
}

char cc_instantGetChar(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	/* Save console mode */
	DWORD saveMode;
	if(!GetConsoleMode(ccc->hStdIn, &saveMode)) {
		LOG_ERROR("GetConsoleMode failed (error %lu)", GetLastError());
		return 0;
	}
	if(!SetConsoleMode(ccc->hStdIn, ENABLE_PROCESSED_INPUT)) {
		LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
		return 0;
	}

	TCHAR ch = 0;
	if(WaitForSingleObject(ccc->hStdIn, INFINITE) == WAIT_OBJECT_0) {
		DWORD num;
		if(!ReadConsole(ccc->hStdIn, &ch, 1, &num, NULL)) {
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
	if(!SetConsoleMode(ccc->hStdIn, saveMode)) {
		LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
	}
	return ch;
}

bool cc_waitingInput(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	DWORD num;
	if(!GetNumberOfConsoleInputEvents(ccc->hStdIn, &num)) {
		LOG_ERROR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
		return false;
	}

	return (num > 1);
}

void cc_displayInputs(cc_Handle cch, bool display) {
	cc_Context* ccc = (cc_Context*) cch;

	/* Get console mode */
	DWORD mode;
	if(!GetConsoleMode(ccc->hStdIn, &mode)) {
		LOG_ERROR("GetConsoleMode failed (error %lu)", GetLastError());
		return;
	}

	if(display) {
		/* Add echo input to the mode */
		if(!SetConsoleMode(ccc->hStdIn, mode | ENABLE_ECHO_INPUT)) {
			LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
			return;
		}
	}
	else {
		/* Remove echo input to the mode */
		if(!SetConsoleMode(ccc->hStdIn, mode & ~((DWORD) ENABLE_ECHO_INPUT))) {
			LOG_ERROR("SetConsoleMode failed (error %lu)", GetLastError());
			return;
		}
	}
}

static WORD processedInputsNb = 0;

cc_Input cc_getInput(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;
	cc_Input input = {OTHER_KEY, 0};
	DWORD num;

	/* Get number of input event */
	if(!GetNumberOfConsoleInputEvents(ccc->hStdIn, &num)) {
		LOG_ERROR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
		return input;
	}

	/* If there is no input event wait one */
	if(num < 1) {
		if(WaitForSingleObject(ccc->hStdIn, INFINITE) != WAIT_OBJECT_0) {
			LOG_ERROR("WaitForSingleObject failed (error %lu)", GetLastError());
			return input;
		}
	}

	/* Read the first event that is a key pressed event */
	INPUT_RECORD event;
	if(!PeekConsoleInput(ccc->hStdIn, &event, 1, &num)) {
		LOG_ERROR("PeekConsoleInput failed (error %lu)", GetLastError());
		return input;
	}
	if(num < 1) {
		LOG_ERROR("WaitForSingleObject returned without an input event");
		return input;
	}
	while(event.EventType != KEY_EVENT || !event.Event.KeyEvent.bKeyDown) {
		/* Not a key pressed event, remove it from the console input buffer */
		if(!ReadConsoleInput(ccc->hStdIn, &event, 1, &num)) {
			LOG_ERROR("ReadConsoleInput failed (error %lu)", GetLastError());
			return input;
		}

		/* Get number of input event */
		if(!GetNumberOfConsoleInputEvents(ccc->hStdIn, &num)) {
			LOG_ERROR("GetNumberOfConsoleInputEvents failed (error %lu)", GetLastError());
			return input;
		}

		/* If there is no input event wait one */
		if(num < 1) {
			if(WaitForSingleObject(ccc->hStdIn, INFINITE) != WAIT_OBJECT_0) {
				LOG_ERROR("WaitForSingleObject failed (error %lu)", GetLastError());
				return input;
			}
		}

		if(!PeekConsoleInput(ccc->hStdIn, &event, 1, &num)) {
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
		if(!ReadConsoleInput(ccc->hStdIn, &event, 1, &num)) {
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
		input.ch = cc_getAssociatedChar(cch, input.key);
	}

	return input;
}

// functions from WindowsConsoleControl.h

cc_Vector2 cc_getCursorPosition(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
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

cc_Vector2 cc_getCursorGlobalPosition(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
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

void cc_reverseColors(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(ccc->hStdOut, csbi.wAttributes | (WORD) COMMON_LVB_REVERSE_VIDEO)) {
		LOG_ERROR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

int cc_getGlobalWidth(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.dwSize.X;
}

int cc_getGlobalHeight(cc_Handle cch) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return 0;
	}

	return csbi.dwSize.Y;
}

void cc_setCursorGlobalPosition(cc_Handle cch, const cc_Vector2 position) {
	cc_Context* ccc = (cc_Context*) cch;

	COORD pos = {
		(SHORT) position.x,
		(SHORT) position.y
	};
	if(!SetConsoleCursorPosition(ccc->hStdOut, pos)) {
		LOG_ERROR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

cc_Vector2 cc_globalClamp(cc_Handle cch, const cc_Vector2 position) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return position;
	}

	int maxX = csbi.dwSize.X - 1;
	int maxY = csbi.dwSize.Y - 1;
	cc_Vector2 result = {
		position.x < maxX ? (position.x < 0 ? 0 : position.x) : maxX,
		position.y < maxY ? (position.y < 0 ? 0 : position.y) : maxY
	};
	return result;
}

bool cc_globalContains(cc_Handle cch, const cc_Vector2 position) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(ccc->hStdOut, &csbi)) {
		LOG_ERROR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return false;
	}

	return position.x >= 0
	       && position.y >= 0
	       && position.x < csbi.dwSize.X
	       && position.y < csbi.dwSize.Y;
}

void cc_setCursorSize(cc_Handle cch, unsigned int size) {
	cc_Context* ccc = (cc_Context*) cch;

	CONSOLE_CURSOR_INFO cci;
	if(!GetConsoleCursorInfo(ccc->hStdOut, &cci)) {
		LOG_ERROR("GetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}

	if(size < 100) {
		cci.dwSize = size;
	}
	else {
		cci.dwSize = 100;
	}

	if(!SetConsoleCursorInfo(ccc->hStdOut, &cci)) {
		LOG_ERROR("SetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}
}

#endif //_WIN32
