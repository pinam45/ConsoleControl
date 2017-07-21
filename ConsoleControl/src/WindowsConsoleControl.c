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

#include <WindowsConsoleControl.h>

#ifdef OS_WINDOWS

cc_Vector2 cc_getCursorPosition() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		cc_Vector2 position = {0, 0};
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
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
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		cc_Vector2 position = {0, 0};
		return position;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
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
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		LOG_ERR("GetConsoleScreenBufferInfo failed (error %lu)", GetLastError());
		return;
	}

	if(!SetConsoleTextAttribute(hStdOut, csbi.wAttributes | (WORD) COMMON_LVB_REVERSE_VIDEO)) {
		LOG_ERR("SetConsoleTextAttribute failed (error %lu)", GetLastError());
		return;
	}
}

cc_type cc_getGlobalWidth() {
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

	return csbi.dwSize.X;
}

cc_type cc_getGlobalHeight() {
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

	return csbi.dwSize.Y;
}

void cc_setCursorGlobalPosition(const cc_Vector2 position) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdOut == INVALID_HANDLE_VALUE) {
		LOG_ERR("GetStdHandle failed (error %lu)", GetLastError());
		return;
	}

	COORD pos = {
		(short) position.x,
		(short) position.y
	};
	if(!SetConsoleCursorPosition(hStdOut, pos)) {
		LOG_ERR("SetConsoleCursorPosition failed (error %lu)", GetLastError());
		return;
	}
}

cc_Vector2 cc_globalClamp(const cc_Vector2 position) {
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
	       && position.x < csbi.dwSize.X
	       && position.y < csbi.dwSize.Y;
}

void cc_setCursorSize(unsigned int size) {
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

	if(size < 100) {
		cci.dwSize = size;
	}
	else {
		cci.dwSize = 100;
	}

	if(!SetConsoleCursorInfo(hStdOut, &cci)) {
		LOG_ERR("SetConsoleCursorInfo failed (error %lu)", GetLastError());
		return;
	}
}

#endif //OS_WINDOWS
