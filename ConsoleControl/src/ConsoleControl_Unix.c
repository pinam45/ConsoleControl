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

#ifndef _WIN32

#include <UnixConsoleControl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <log.h>
#include <ConsoleControlColor.h>
#include <ConsoleControlInput.h>

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

// functions from ConsoleControl.h

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
		LOG_ERROR("ioctl failed");
		return 0;
	}

	return w.ws_col;
}

cc_type cc_getHeight() {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		LOG_ERROR("ioctl failed");
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
		LOG_ERROR("ioctl failed");
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
		LOG_ERROR("ioctl failed");
		return x;
	}

	cc_type maxX = w.ws_col - 1;
	return x < maxX ? (x < 0 ? 0 : x) : maxX;
}

cc_type cc_clampY(cc_type y) {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		LOG_ERROR("ioctl failed");
		return y;
	}

	cc_type maxY = w.ws_row - 1;
	return y < maxY ? (y < 0 ? 0 : y) : maxY;
}

bool cc_contains(cc_Vector2 position) {
	struct winsize w;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		LOG_ERROR("ioctl failed");
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
		LOG_ERROR("tcgetattr failed (%s)", strerror(errno));
		return 0;
	}

	/* Set console mode to non canonical (return without waiting '\n') */
	newt = oldt;
	newt.c_lflag &= ~((tcflag_t) ICANON);        // non canonical
	newt.c_cc[VMIN] = 1;                         // read only 1 character
	newt.c_cc[VTIME] = 0;                        // forever wait for an input
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &newt)) {
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
		return 0;
	}

	/* Wait and take first stdin char */
	ch = (char) getchar();

	/* Restore console mode */
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &oldt)) {
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
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
		LOG_ERROR("tcgetattr failed (%s)", strerror(errno));
		return false;
	}

	/* Set console mode to non canonical (return without waiting '\n') and no echo */
	newt = oldt;
	newt.c_lflag &= ~((tcflag_t)(ICANON | ECHO));
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &newt)) {
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
		return false;
	}

	/* Save stdin file status flags */
	errno = 0;
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	if(errno) {
		LOG_ERROR("fcntl failed (%s)", strerror(errno));
		return false;
	}

	/* Add non blocking to file status flags, to avoid waiting user input if stdin is empty */
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	if(errno) {
		LOG_ERROR("fcntl failed (%s)", strerror(errno));
		return false;
	}

	/* Take first stdin char */
	ch = getchar();

	/* Restore console mode */
	errno = 0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &oldt)) {
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
		return false;
	}

	/* Restore stdin file status flags */
	errno = 0;
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if(errno) {
		LOG_ERROR("fcntl failed (%s)", strerror(errno));
		return false;
	}

	/* Check if stdin was empty */
	if(ch != EOF) {
		errno = 0;
		/* Put back the taken char */
		if(ungetc(ch, stdin) == EOF) {
			LOG_ERROR("ungetc failed (%s)", strerror(errno));
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
		LOG_ERROR("tcgetattr failed (%s)", strerror(errno));
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
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
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
		LOG_ERROR("tcgetattr failed (%s)", strerror(errno));
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
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
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
			LOG_ERROR("ungetc failed (%s)", strerror(errno));
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
		LOG_ERROR("tcsetattr failed (%s)", strerror(errno));
		free(inputChar);
		return input;
	}

	free(inputChar);
	return input;
}

// functions from UnixConsoleControl.h

void cc_permanentReverseColors() {
	printf(CSI SGR_REVERSE_VALUE SGR_CODE);
}

#endif //_WIN32
