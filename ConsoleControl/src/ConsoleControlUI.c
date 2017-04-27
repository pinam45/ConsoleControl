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

#include <ConsoleControlUI.h>

typedef struct {
	unsigned int width;
	unsigned int height;
	cc_Vector2 topLeft;
} MenuDrawInfo;

static const cc_Vector2 nullpos = {0, 0};

// For cc_displayTableMenu
static MenuDrawInfo computeTableMenuDrawInfo(const cc_Menu* menu);

// For cc_displayTableMenu
static void drawTableMenuChoices(const MenuDrawInfo* info, const cc_Menu* menu);

// For cc_displayTableMenu
static void drawTableMenu(const MenuDrawInfo* info, const cc_Menu* menu);

// For cc_displayColorMenu
static MenuDrawInfo computeColorMenuDrawInfo(const cc_Menu* menu);

// For cc_displayTableMenu
static void drawColorMenuChoices(const MenuDrawInfo* info, const cc_Menu* menu, const cc_MenuColors* colors);

// For cc_displayColorMenu
static void drawColorMenu(const MenuDrawInfo* info, const cc_Menu* menu, const cc_MenuColors* colors);


static MenuDrawInfo computeTableMenuDrawInfo(const cc_Menu* menu) {

	unsigned int maxLength = (unsigned int) strlen(menu->title);
	unsigned int len;
	/* Compute maxLength */
	for(unsigned int i = menu->choicesNumber; i--;) {
		len = (unsigned int) strlen(menu->choices[i]);
		if(len > maxLength) {
			maxLength = len;
		}
	}

	MenuDrawInfo info;
	info.width = maxLength + 7;
	info.height = menu->choicesNumber * 2 + 6;
	info.topLeft.x = (cc_getWidth() - (cc_type) info.width) / 2;
	info.topLeft.y = (cc_getHeight() - (cc_type) info.height) / 2;

	return info;
}

static void drawTableMenuChoices(const MenuDrawInfo* info, const cc_Menu* menu) {

	cc_Vector2 pos;
	for(unsigned int i = menu->choicesNumber; i--;) {
		pos.x = info->topLeft.x + (cc_type) (info->width - (unsigned int) strlen(menu->choices[i])) / 2 - 1;
		pos.y = info->topLeft.y + (cc_type) (4 + 2 * (i + 1));
		cc_setCursorPosition(pos);
		if(menu->currentChoice == i) {
			printf("> %s <", menu->choices[i]);
		}
		else {
			printf("  %s  ", menu->choices[i]);
		}
	}
}

static void drawTableMenu(const MenuDrawInfo* info, const cc_Menu* menu) {

	cc_Vector2 topLeft = info->topLeft;
	cc_Vector2 downRight = {
		topLeft.x + (cc_type) info->width,
		topLeft.y + (cc_type) info->height
	};

	cc_clean();

	/* Print table and title */
	cc_drawTableRectangle(topLeft, downRight);
	topLeft.y += 2;
	cc_Vector2 pos = {
		topLeft.x + (cc_type) (info->width - (unsigned int) strlen(menu->title)) / 2 + 1,
		topLeft.y
	};
	cc_setCursorPosition(pos);
	printf("%s", menu->title);
	topLeft.y += 2;
	cc_Vector2 topright = {
		downRight.x,
		topLeft.y
	};
	cc_drawTableHorizontalLine(topLeft, topright);

	/* Print the choices */
	drawTableMenuChoices(info, menu);
}

static MenuDrawInfo computeColorMenuDrawInfo(const cc_Menu* menu) {

	unsigned int maxLength = (unsigned int) strlen(menu->title);
	unsigned int len;
	/* Compute maxLength */
	for(unsigned int i = menu->choicesNumber; i--;) {
		len = (unsigned int) strlen(menu->choices[i]);
		if(len > maxLength) {
			maxLength = len;
		}
	}

	MenuDrawInfo info;
	info.width = maxLength + 5;
	info.height = menu->choicesNumber * 2 + 5;
	info.topLeft.x = (cc_getWidth() - (cc_type) info.width) / 2;
	info.topLeft.y = (cc_getHeight() - (cc_type) info.height) / 2;

	return info;
}

static void drawColorMenuChoices(const MenuDrawInfo* info, const cc_Menu* menu, const cc_MenuColors* colors) {

	cc_Vector2 pos;
	pos.x = info->topLeft.x + 1;

	for(unsigned int i = menu->choicesNumber; i--;) {
		pos.y = info->topLeft.y + (cc_type) (4 + (2 * i));
		cc_setCursorPosition(pos);
		if(menu->currentChoice == i) {
			cc_setColors(colors->selectionBackgroundColor, colors->selectionForegroundColor);
		}
		unsigned j = 0;
		for(; j < (info->width - (unsigned int) strlen(menu->choices[i])) / 2; ++j) {
			putchar(' ');
		}
		printf("%s", menu->choices[i]);
		j += (unsigned int) strlen(menu->choices[i]);
		for(; j < info->width - 1; ++j) {
			putchar(' ');
		}
		if(menu->currentChoice == i) {
			cc_setColors(colors->choicesBackgroundColor, colors->choicesForegroundColor);
		}
	}
}

static void drawColorMenu(const MenuDrawInfo* info, const cc_Menu* menu, const cc_MenuColors* colors) {

	cc_Vector2 topLeft = info->topLeft;
	cc_Vector2 downRight = { // downRight for the title
		topLeft.x + (cc_type) info->width,
		topLeft.y + 3
	};

	cc_setBackgroundColor(colors->mainBackgroundColor);
	cc_clean();

	/* Print the title background and text */
	cc_setColors(colors->titleBackgroundColor, colors->titleForegroundColor);
	cc_drawFullRectangle(topLeft, downRight, ' ');
	++topLeft.y;
	cc_Vector2 pos = {
		topLeft.x + (cc_type) (info->width - (unsigned int) strlen(menu->title)) / 2 + 1,
		topLeft.y
	};
	cc_setCursorPosition(pos);
	printf("%s", menu->title);

	/* If same background color for title and choices, draw a line */
	if(colors->titleBackgroundColor == colors->choicesBackgroundColor) {
		++topLeft.y;
		--downRight.y;
		cc_drawLine(topLeft, downRight, '_');
		++topLeft.y;
	}
	else {
		topLeft.y += 2;
	}
	// topLeft is now for the choices background

	/* Print the choices background */
	downRight.y = topLeft.y + (cc_type) info->height - 5; // downRight for the choices
	cc_setColors(colors->choicesBackgroundColor, colors->choicesForegroundColor);
	cc_drawFullRectangle(topLeft, downRight, ' ');

	/* Print the choices */
	drawColorMenuChoices(info, menu, colors);
}

void cc_displayTableMenu(cc_Menu* menu) {

	cc_type consoleWidth = cc_getWidth();
	cc_type consoleHeight = cc_getHeight();
	cc_type usedWidth = consoleWidth;
	cc_type usedHeight = consoleHeight;

	MenuDrawInfo info = computeTableMenuDrawInfo(menu);

	drawTableMenu(&info, menu);
	cc_setCursorPosition(nullpos);

	/* Main loop */
	cc_displayInputs(false);
	cc_Input input;
	bool exit = false;
	while(!exit) {
		input = cc_getInput();
		switch(input.key) {
			case PAGE_UP_KEY:
				menu->currentChoice = 0;
				break;
			case PAGE_DOWN_KEY:
				menu->currentChoice = menu->choicesNumber - 1;
				break;
			case UP_ARROW_KEY:
				if(menu->currentChoice) {
					--menu->currentChoice;
				}
				else {
					menu->currentChoice = menu->choicesNumber - 1;
				}
				break;
			case DOWN_ARROW_KEY:
				++menu->currentChoice;
				menu->currentChoice %= menu->choicesNumber;
				break;
			case ENTER_KEY:
				exit = true;
				break;
			case ESC_KEY:
				if(menu->choiceOnEscape >= 0 && (unsigned int) (menu->choiceOnEscape) < menu->choicesNumber) {
					menu->currentChoice = (unsigned int) menu->choiceOnEscape;
					exit = true;
				}
				break;
			case HOME_KEY:break;
			case END_KEY:break;
			case LEFT_ARROW_KEY:break;
			case RIGHT_ARROW_KEY:break;
			case BACKSPACE_KEY:break;
			case TAB_KEY:break;
			case SPACE_KEY:break;
			case INS_KEY:break;
			case DEL_KEY:break;
			case F1_KEY:break;
			case F2_KEY:break;
			case F3_KEY:break;
			case F4_KEY:break;
			case F5_KEY:break;
			case F6_KEY:break;
			case F7_KEY:break;
			case F8_KEY:break;
			case F9_KEY:break;
			case F10_KEY:break;
			case F11_KEY:break;
			case F12_KEY:break;
			case OTHER_KEY:break;
			default:break;
		}

		consoleWidth = cc_getWidth();
		consoleHeight = cc_getHeight();
		if(usedWidth == consoleWidth && usedHeight == consoleHeight) {
			drawTableMenuChoices(&info, menu);
		}
		else {
			usedWidth = consoleWidth;
			usedHeight = consoleHeight;
			info = computeTableMenuDrawInfo(menu);
			drawTableMenu(&info, menu);
		}
		cc_setCursorPosition(nullpos);
	}
}

void cc_displayColorMenu(cc_Menu* menu, const cc_MenuColors* colors) {

	cc_type consoleWidth = cc_getWidth();
	cc_type consoleHeight = cc_getHeight();
	cc_type usedWidth = consoleWidth;
	cc_type usedHeight = consoleHeight;

	MenuDrawInfo info = computeColorMenuDrawInfo(menu);

	drawColorMenu(&info, menu, colors);
	cc_setCursorPosition(nullpos);

	/* Main loop */
	cc_displayInputs(false);
	cc_Input input;
	bool exit = false;
	while(!exit) {
		input = cc_getInput();
		switch(input.key) {
			case PAGE_UP_KEY:
				menu->currentChoice = 0;
				break;
			case PAGE_DOWN_KEY:
				menu->currentChoice = menu->choicesNumber - 1;
				break;
			case UP_ARROW_KEY:
				if(menu->currentChoice) {
					--menu->currentChoice;
				}
				else {
					menu->currentChoice = menu->choicesNumber - 1;
				}
				break;
			case DOWN_ARROW_KEY:
				++menu->currentChoice;
				menu->currentChoice %= menu->choicesNumber;
				break;
			case ENTER_KEY:
				exit = true;
				break;
			case ESC_KEY:
				if(menu->choiceOnEscape >= 0 && (unsigned int) (menu->choiceOnEscape) < menu->choicesNumber) {
					menu->currentChoice = (unsigned int) menu->choiceOnEscape;
					exit = true;
				}
				break;
			case HOME_KEY:break;
			case END_KEY:break;
			case LEFT_ARROW_KEY:break;
			case RIGHT_ARROW_KEY:break;
			case BACKSPACE_KEY:break;
			case TAB_KEY:break;
			case SPACE_KEY:break;
			case INS_KEY:break;
			case DEL_KEY:break;
			case F1_KEY:break;
			case F2_KEY:break;
			case F3_KEY:break;
			case F4_KEY:break;
			case F5_KEY:break;
			case F6_KEY:break;
			case F7_KEY:break;
			case F8_KEY:break;
			case F9_KEY:break;
			case F10_KEY:break;
			case F11_KEY:break;
			case F12_KEY:break;
			case OTHER_KEY:break;
			default:break;
		}

		consoleWidth = cc_getWidth();
		consoleHeight = cc_getHeight();
		if(usedWidth == consoleWidth && usedHeight == consoleHeight) {
			drawColorMenuChoices(&info, menu, colors);
		}
		else {
			usedWidth = consoleWidth;
			usedHeight = consoleHeight;
			info = computeColorMenuDrawInfo(menu);
			drawColorMenu(&info, menu, colors);
		}
		cc_setCursorPosition(nullpos);
	}
}
