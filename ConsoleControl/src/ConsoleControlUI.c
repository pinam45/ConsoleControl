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

typedef struct {
	unsigned int width;
	unsigned int height;
	cc_Vector2 topLeft;
	unsigned int linesNumber;
	bool hasTitle;
	bool hasChoices;
	unsigned int leftChoicePosX;
	unsigned int middleChoicePosX;
	unsigned int rightChoicePosX;
} MessageDrawInfo;

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

// For cc_displayTableMessage and cc_displayColorMessage
static inline bool messageHasChoices(const cc_Message* message);

// For cc_displayTableMessage
static MessageDrawInfo computeTableMessageDrawInfo(const cc_Message* message, char** messageLines,
                                                   unsigned int linesNumber);

// For cc_displayTableMessage
static void drawTableMessageChoices(const MessageDrawInfo* info, const cc_Message* message);

// For cc_displayTableMessage
static void drawTableMessage(const MessageDrawInfo* info, const cc_Message* message, char** messageLines);

// For cc_displayColorMessage
static MessageDrawInfo computeColorMessageDrawInfo(const cc_Message* message, char** messageLines,
                                                   unsigned int linesNumber);

// For cc_displayColorMessage
static void drawColorMessageChoices(const MessageDrawInfo* info, const cc_Message* message,
                                    const cc_MessageColors* colors);

// For cc_displayColorMessage
static void drawColorMessage(const MessageDrawInfo* info, const cc_Message* message,
                             char** messageLines, const cc_MessageColors* colors);

MenuDrawInfo computeTableMenuDrawInfo(const cc_Menu* menu) {

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

void drawTableMenuChoices(const MenuDrawInfo* info, const cc_Menu* menu) {

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

void drawTableMenu(const MenuDrawInfo* info, const cc_Menu* menu) {

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

MenuDrawInfo computeColorMenuDrawInfo(const cc_Menu* menu) {

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

void drawColorMenuChoices(const MenuDrawInfo* info, const cc_Menu* menu, const cc_MenuColors* colors) {

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

void drawColorMenu(const MenuDrawInfo* info, const cc_Menu* menu, const cc_MenuColors* colors) {

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

bool messageHasChoices(const cc_Message* message) {
	return (message->leftChoice != NULL && message->leftChoice[0] != '\0')
	       || (message->middleChoice != NULL && message->middleChoice[0] != '\0')
	       || (message->rightChoice != NULL && message->rightChoice[0] != '\0');
}

MessageDrawInfo computeTableMessageDrawInfo(const cc_Message* message, char** messageLines, unsigned int linesNumber) {

	MessageDrawInfo info;
	info.linesNumber = linesNumber;
	info.hasTitle = (message->title != NULL && message->title[0] != '\0');

	/* Compute maxLength */
	unsigned int maxLength = 0;
	if(info.hasTitle) {
		maxLength = (unsigned int) strlen(message->title);
	}
	unsigned int len;
	while(linesNumber--) {
		len = (unsigned int) strlen(messageLines[linesNumber]);
		if(len > maxLength) {
			maxLength = len;
		}
	}

	info.hasChoices = messageHasChoices(message);
	if(info.hasChoices) {
		/* Compute choices lengths and update maxLength */
		len = 0;
		unsigned int leftChoiceLen = 0;
		unsigned int middleChoiceLen = 0;
		unsigned int rightChoiceLen = 0;
		if(message->leftChoice != NULL) {
			leftChoiceLen = (unsigned int) strlen(message->leftChoice) + 4;
		}
		len += leftChoiceLen;
		if(message->middleChoice != NULL) {
			middleChoiceLen = (unsigned int) strlen(message->middleChoice) + 4;
		}
		len += middleChoiceLen;
		if(message->rightChoice != NULL) {
			rightChoiceLen = (unsigned int) strlen(message->rightChoice) + 4;
		}
		len += rightChoiceLen;
		if(len > maxLength) {
			maxLength = len;
		}

		/* Set information */
		info.width = maxLength + 5;
		info.height = info.linesNumber + 5 + (unsigned int) (4 * info.hasTitle);
		info.topLeft.x = (cc_getWidth() - (cc_type) info.width) / 2;
		info.topLeft.y = (cc_getHeight() - (cc_type) info.height) / 2;

		/* Set choices X positions */
		if(message->leftChoice != NULL) {
			info.leftChoicePosX = (unsigned int) (info.topLeft.x + 2);
		}
		if(message->rightChoice != NULL) {
			info.rightChoicePosX = (unsigned int) (info.topLeft.x) + info.width - rightChoiceLen - 1;
		}
		if(message->middleChoice != NULL) {
			info.middleChoicePosX = (unsigned int) (info.topLeft.x) + leftChoiceLen +
			                        (info.width - leftChoiceLen - rightChoiceLen -
			                         (unsigned int) strlen(message->middleChoice)) / 2 - 1;
		}
	}
	else {
		/* Set information */
		info.width = maxLength + 5;
		info.height = info.linesNumber + 3 + (unsigned int) (4 * info.hasTitle);
		info.topLeft.x = (cc_getWidth() - (cc_type) info.width) / 2;
		info.topLeft.y = (cc_getHeight() - (cc_type) info.height) / 2;
	}

	return info;
}

void drawTableMessageChoices(const MessageDrawInfo* info, const cc_Message* message) {
	cc_Vector2 pos;
	pos.y = info->topLeft.y + (int) (info->linesNumber + 3 + (unsigned int) (4 * info->hasTitle));
	/* Left choice */
	if(message->leftChoice != NULL && message->leftChoice[0] != '\0') {
		pos.x = (int) (info->leftChoicePosX);
		cc_setCursorPosition(pos);
		if(message->currentChoice == LEFT_CHOICE) {
			printf("> %s <", message->leftChoice);
		}
		else {
			printf("  %s  ", message->leftChoice);
		}
	}
	/* Middle choice */
	if(message->middleChoice != NULL && message->middleChoice[0] != '\0') {
		pos.x = (int) (info->middleChoicePosX);
		cc_setCursorPosition(pos);
		if(message->currentChoice == MIDDLE_CHOICE) {
			printf("> %s <", message->middleChoice);
		}
		else {
			printf("  %s  ", message->middleChoice);
		}
	}
	/* Right choice */
	if(message->rightChoice != NULL && message->rightChoice[0] != '\0') {
		pos.x = (int) (info->rightChoicePosX);
		cc_setCursorPosition(pos);
		if(message->currentChoice == RIGHT_CHOICE) {
			printf("> %s <", message->rightChoice);
		}
		else {
			printf("  %s  ", message->rightChoice);
		}
	}
}

void drawTableMessage(const MessageDrawInfo* info, const cc_Message* message, char** messageLines) {

	cc_Vector2 topLeft = info->topLeft;
	cc_Vector2 downRight = {
		topLeft.x + (cc_type) info->width,
		topLeft.y + (cc_type) info->height
	};

	cc_clean();

	/* Print table and title */
	cc_drawTableRectangle(topLeft, downRight);
	if(info->hasTitle) {
		topLeft.y += 2;
		cc_Vector2 pos = {
			topLeft.x + (cc_type) (info->width - (unsigned int) strlen(message->title)) / 2 + 1,
			topLeft.y
		};
		cc_setCursorPosition(pos);
		printf("%s", message->title);
		topLeft.y += 2;
		cc_Vector2 titleDownRight = {
			downRight.x,
			topLeft.y
		};
		cc_drawTableHorizontalLine(topLeft, titleDownRight);
	}

	/* Print message */
	topLeft.y += (int) (info->linesNumber) + 2;
	for(unsigned int i = info->linesNumber; i--;) {
		--topLeft.y;
		topLeft.x = info->topLeft.x + 1 + (int) (info->width - (unsigned int) strlen(messageLines[i])) / 2;
		cc_setCursorPosition(topLeft);
		printf("%s", messageLines[i]);
	}

	/* Print the choices */
	if(info->hasChoices) {
		drawTableMessageChoices(info, message);
	}
}

MessageDrawInfo computeColorMessageDrawInfo(const cc_Message* message, char** messageLines, unsigned int linesNumber) {

	MessageDrawInfo info;
	info.linesNumber = linesNumber;
	info.hasTitle = (message->title != NULL && message->title[0] != '\0');

	/* Compute maxLength */
	unsigned int maxLength = 0;
	if(info.hasTitle) {
		maxLength = (unsigned int) strlen(message->title);
	}
	unsigned int len;
	while(linesNumber--) {
		len = (unsigned int) strlen(messageLines[linesNumber]);
		if(len > maxLength) {
			maxLength = len;
		}
	}

	info.hasChoices = messageHasChoices(message);
	if(info.hasChoices) {
		/* Compute choices lengths and update maxLength */
		len = 0;
		unsigned int leftChoiceLen = 0;
		unsigned int middleChoiceLen = 0;
		unsigned int rightChoiceLen = 0;
		if(message->leftChoice != NULL) {
			leftChoiceLen = (unsigned int) strlen(message->leftChoice) + 2;
		}
		len += leftChoiceLen;
		if(message->middleChoice != NULL) {
			middleChoiceLen = (unsigned int) strlen(message->middleChoice) + 2;
		}
		len += middleChoiceLen;
		if(message->rightChoice != NULL) {
			rightChoiceLen = (unsigned int) strlen(message->rightChoice) + 2;
		}
		len += rightChoiceLen;
		if(len > maxLength) {
			maxLength = len;
		}

		/* Set information */
		info.width = maxLength + 3;
		info.height = info.linesNumber + 3 + (unsigned int) (3 * info.hasTitle);
		info.topLeft.x = (cc_getWidth() - (cc_type) info.width) / 2;
		info.topLeft.y = (cc_getHeight() - (cc_type) info.height) / 2;

		/* Set choices X positions */
		if(message->leftChoice != NULL) {
			info.leftChoicePosX = (unsigned int) (info.topLeft.x + 1);
		}
		if(message->rightChoice != NULL) {
			info.rightChoicePosX = (unsigned int) (info.topLeft.x) + info.width - rightChoiceLen;
		}
		if(message->middleChoice != NULL) {
			info.middleChoicePosX = (unsigned int) (info.topLeft.x) + leftChoiceLen +
			                        (info.width - leftChoiceLen - rightChoiceLen -
			                         (unsigned int) strlen(message->middleChoice)) / 2;
		}
	}
	else {
		/* Set information */
		info.width = maxLength + 3;
		info.height = info.linesNumber + 1 + (unsigned int) (3 * info.hasTitle);
		info.topLeft.x = (cc_getWidth() - (cc_type) info.width) / 2;
		info.topLeft.y = (cc_getHeight() - (cc_type) info.height) / 2;
	}

	return info;
}

void drawColorMessageChoices(const MessageDrawInfo* info, const cc_Message* message, const cc_MessageColors* colors) {
	cc_Vector2 pos;
	pos.y = info->topLeft.y + (int) (info->linesNumber + 2 + (unsigned int) (3 * info->hasTitle));
	/* Left choice */
	if(message->leftChoice != NULL && message->leftChoice[0] != '\0') {
		pos.x = (int) (info->leftChoicePosX);
		cc_setCursorPosition(pos);
		if(message->currentChoice == LEFT_CHOICE) {
			cc_setColors(colors->selectionBackgroundColor, colors->selectionForegroundColor);
		}
		else {
			cc_setColors(colors->choicesBackgroundColor, colors->choicesForegroundColor);
		}
		printf(" %s ", message->leftChoice);
	}
	/* Middle choice */
	if(message->middleChoice != NULL && message->middleChoice[0] != '\0') {
		pos.x = (int) (info->middleChoicePosX);
		cc_setCursorPosition(pos);
		if(message->currentChoice == MIDDLE_CHOICE) {
			cc_setColors(colors->selectionBackgroundColor, colors->selectionForegroundColor);
		}
		else {
			cc_setColors(colors->choicesBackgroundColor, colors->choicesForegroundColor);
		}
		printf(" %s ", message->middleChoice);
	}
	/* Right choice */
	if(message->rightChoice != NULL && message->rightChoice[0] != '\0') {
		pos.x = (int) (info->rightChoicePosX);
		cc_setCursorPosition(pos);
		if(message->currentChoice == RIGHT_CHOICE) {
			cc_setColors(colors->selectionBackgroundColor, colors->selectionForegroundColor);
		}
		else {
			cc_setColors(colors->choicesBackgroundColor, colors->choicesForegroundColor);
		}
		printf(" %s ", message->rightChoice);
	}
}

void drawColorMessage(const MessageDrawInfo* info, const cc_Message* message,
                      char** messageLines, const cc_MessageColors* colors) {

	cc_Vector2 topLeft = info->topLeft;
	cc_Vector2 downRight = { // downRight for the title
		topLeft.x + (cc_type) info->width,
		topLeft.y + 3
	};

	cc_setBackgroundColor(colors->mainBackgroundColor);
	cc_clean();

	/* Print the title background and text */
	if(info->hasTitle) {
		cc_setColors(colors->titleBackgroundColor, colors->titleForegroundColor);
		cc_drawFullRectangle(topLeft, downRight, ' ');
		++topLeft.y;
		cc_Vector2 pos = {
			topLeft.x + (cc_type) (info->width - (unsigned int) strlen(message->title)) / 2 + 1,
			topLeft.y
		};
		cc_setCursorPosition(pos);
		printf("%s", message->title);

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
		// topLeft is now for the message background
	}

	/* Print the message and choices background */
	downRight.y = topLeft.y + (cc_type) info->height - 3 * info->hasTitle; // downRight for the message and choices
	cc_setColors(colors->messageBackgroundColor, colors->messageForegroundColor);
	cc_drawFullRectangle(topLeft, downRight, ' ');

	/* Print message */
	topLeft.y += (int) (info->linesNumber) + 1;
	for(unsigned int i = info->linesNumber; i--;) {
		--topLeft.y;
		topLeft.x = info->topLeft.x + 1 + (int) (info->width - (unsigned int) strlen(messageLines[i])) / 2;
		cc_setCursorPosition(topLeft);
		printf("%s", messageLines[i]);
	}

	/* Print the choices */
	if(info->hasChoices) {
		drawColorMessageChoices(info, message, colors);
	}
}

void cc_displayTableMenu(cc_Menu* menu) {

	if(menu->title == NULL) {
		SLOG_ERR("Menu title field is NULL");
		return;
	}
	if(menu->choices == NULL) {
		SLOG_ERR("Menu choices field is NULL");
		return;
	}
	if(menu->choicesNumber == 0) {
		SLOG_ERR("Menu choicesNumber field is 0");
		return;
	}
	if(menu->currentChoice > menu->choicesNumber - 1) {
		menu->currentChoice = menu->choicesNumber - 1;
	}

	cc_type consoleWidth = cc_getWidth();
	cc_type consoleHeight = cc_getHeight();
	cc_type usedWidth = consoleWidth;
	cc_type usedHeight = consoleHeight;

	MenuDrawInfo info = computeTableMenuDrawInfo(menu);

	/* Display menu */
	drawTableMenu(&info, menu);

	/* Main loop */
	cc_displayInputs(false);
	cc_setCursorVisibility(false);
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
			case HOME_KEY:
			case END_KEY:
			case LEFT_ARROW_KEY:
			case RIGHT_ARROW_KEY:
			case BACKSPACE_KEY:
			case TAB_KEY:
			case SPACE_KEY:
			case INS_KEY:
			case DEL_KEY:
			case F1_KEY:
			case F2_KEY:
			case F3_KEY:
			case F4_KEY:
			case F5_KEY:
			case F6_KEY:
			case F7_KEY:
			case F8_KEY:
			case F9_KEY:
			case F10_KEY:
			case F11_KEY:
			case F12_KEY:
			case OTHER_KEY:
			default:
				break;
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
	}

	cc_setCursorPosition(nullpos);
}

void cc_displayColorMenu(cc_Menu* menu, const cc_MenuColors* colors) {

	if(menu->title == NULL) {
		SLOG_ERR("Menu title field is NULL");
		return;
	}
	if(menu->choices == NULL) {
		SLOG_ERR("Menu choices field is NULL");
		return;
	}
	if(menu->choicesNumber == 0) {
		SLOG_ERR("Menu choicesNumber field is 0");
		return;
	}
	if(menu->currentChoice > menu->choicesNumber - 1) {
		menu->currentChoice = menu->choicesNumber - 1;
	}

	cc_type consoleWidth = cc_getWidth();
	cc_type consoleHeight = cc_getHeight();
	cc_type usedWidth = consoleWidth;
	cc_type usedHeight = consoleHeight;

	MenuDrawInfo info = computeColorMenuDrawInfo(menu);

	/* Display menu */
	drawColorMenu(&info, menu, colors);

	/* Main loop */
	cc_displayInputs(false);
	cc_setCursorVisibility(false);
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
			case HOME_KEY:
			case END_KEY:
			case LEFT_ARROW_KEY:
			case RIGHT_ARROW_KEY:
			case BACKSPACE_KEY:
			case TAB_KEY:
			case SPACE_KEY:
			case INS_KEY:
			case DEL_KEY:
			case F1_KEY:
			case F2_KEY:
			case F3_KEY:
			case F4_KEY:
			case F5_KEY:
			case F6_KEY:
			case F7_KEY:
			case F8_KEY:
			case F9_KEY:
			case F10_KEY:
			case F11_KEY:
			case F12_KEY:
			case OTHER_KEY:
			default:
				break;
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
	}

	cc_setCursorPosition(nullpos);
}

void cc_displayTableMessage(cc_Message* message) {

	if(message->message == NULL) {
		SLOG_ERR("Message message field is NULL");
		return;
	}

	char** messageLines = NULL;
	unsigned int stop = 0;
	unsigned int lastStop = stop;
	unsigned int linesNumber = 0;

	/* Split message on multiples lines (at \n) */
	while(true) {
		while(message->message[stop] != '\n' && message->message[stop] != '\0') {
			++stop;
		}
		messageLines = realloc(messageLines, ++linesNumber * sizeof(char*));
		messageLines[linesNumber - 1] = malloc((stop - lastStop) * sizeof(char) + 1);
		strncpy(messageLines[linesNumber - 1], &(message->message[lastStop]), stop - lastStop);
		messageLines[linesNumber - 1][stop - lastStop] = '\0';
		if(message->message[stop] == '\0') {
			break;
		}
		lastStop = ++stop;
	}

	cc_type consoleWidth = cc_getWidth();
	cc_type consoleHeight = cc_getHeight();
	cc_type usedWidth = consoleWidth;
	cc_type usedHeight = consoleHeight;

	MessageDrawInfo info = computeTableMessageDrawInfo(message, messageLines, linesNumber);

	/* Compute available choices */
	cc_MessageChoice choices[4];
	unsigned int choicesNumber = 0;
	unsigned int currentChoice = 4;
	if(info.hasChoices) {
		if(message->leftChoice != NULL && message->leftChoice[0] != '\0') {
			choices[choicesNumber++] = LEFT_CHOICE;
		}
		if(message->middleChoice != NULL && message->middleChoice[0] != '\0') {
			choices[choicesNumber++] = MIDDLE_CHOICE;
		}
		if(message->rightChoice != NULL && message->rightChoice[0] != '\0') {
			choices[choicesNumber++] = RIGHT_CHOICE;
		}
		choices[choicesNumber] = NO_CHOICE;

		/* Find current choice number */
		for(unsigned int i = 0; i < choicesNumber; ++i) {
			if(message->currentChoice == choices[i]) {
				currentChoice = i;
				break;
			}
		}
		/* If current choice not valid, set first choice as current choice */
		if(currentChoice == 4) {
			currentChoice = 0;
			message->currentChoice = choices[currentChoice];
		}
	}
	else {
		message->currentChoice = NO_CHOICE;
	}

	/* Display message */
	drawTableMessage(&info, message, messageLines);

	/* Main loop */
	cc_displayInputs(false);
	cc_setCursorVisibility(false);
	cc_Input input;
	bool exit = false;
	while(!exit) {
		input = cc_getInput();
		if(info.hasChoices) {
			switch(input.key) {
				case HOME_KEY:
					currentChoice = 0;
					break;
				case END_KEY:
					currentChoice = choicesNumber - 1;
					break;
				case LEFT_ARROW_KEY:
					if(currentChoice) {
						--currentChoice;
					}
					else {
						currentChoice = choicesNumber - 1;
					}
					break;
				case RIGHT_ARROW_KEY:
					++currentChoice;
					currentChoice %= choicesNumber;
					break;
				case ENTER_KEY:
					exit = true;
					break;
				case ESC_KEY:
					if(message->canEscape) {
						currentChoice = choicesNumber;
						exit = true;
					}
					break;
				case TAB_KEY:
					++currentChoice;
					currentChoice %= choicesNumber;
					break;
				case PAGE_UP_KEY:
				case PAGE_DOWN_KEY:
				case UP_ARROW_KEY:
				case DOWN_ARROW_KEY:
				case BACKSPACE_KEY:
				case SPACE_KEY:
				case INS_KEY:
				case DEL_KEY:
				case F1_KEY:
				case F2_KEY:
				case F3_KEY:
				case F4_KEY:
				case F5_KEY:
				case F6_KEY:
				case F7_KEY:
				case F8_KEY:
				case F9_KEY:
				case F10_KEY:
				case F11_KEY:
				case F12_KEY:
				case OTHER_KEY:
				default:
					break;
			}
			message->currentChoice = choices[currentChoice];
		}
		else {
			if(input.key == ENTER_KEY || input.key == ESC_KEY) {
				exit = true;
			}
		}

		consoleWidth = cc_getWidth();
		consoleHeight = cc_getHeight();
		if(usedWidth == consoleWidth && usedHeight == consoleHeight) {
			if(info.hasChoices) {
				drawTableMessageChoices(&info, message);
			}
		}
		else {
			usedWidth = consoleWidth;
			usedHeight = consoleHeight;
			info = computeTableMessageDrawInfo(message, messageLines, linesNumber);
			drawTableMessage(&info, message, messageLines);
		}
	}

	while(--linesNumber) {
		free(messageLines[linesNumber]);
	}
	free(messageLines[0]);
	free(messageLines);

	cc_setCursorPosition(nullpos);
}

void cc_displayColorMessage(cc_Message* message, const cc_MessageColors* colors) {

	if(message->message == NULL) {
		SLOG_ERR("Message message field is NULL");
		return;
	}

	char** messageLines = NULL;
	unsigned int stop = 0;
	unsigned int lastStop = stop;
	unsigned int linesNumber = 0;

	/* Split message on multiples lines (at \n) */
	while(true) {
		while(message->message[stop] != '\n' && message->message[stop] != '\0') {
			++stop;
		}
		messageLines = realloc(messageLines, ++linesNumber * sizeof(char*));
		messageLines[linesNumber - 1] = malloc((stop - lastStop) * sizeof(char) + 1);
		strncpy(messageLines[linesNumber - 1], &(message->message[lastStop]), stop - lastStop);
		messageLines[linesNumber - 1][stop - lastStop] = '\0';
		if(message->message[stop] == '\0') {
			break;
		}
		lastStop = ++stop;
	}

	cc_type consoleWidth = cc_getWidth();
	cc_type consoleHeight = cc_getHeight();
	cc_type usedWidth = consoleWidth;
	cc_type usedHeight = consoleHeight;

	MessageDrawInfo info = computeColorMessageDrawInfo(message, messageLines, linesNumber);

	/* Compute available choices */
	cc_MessageChoice choices[4];
	unsigned int choicesNumber = 0;
	unsigned int currentChoice = 4;
	if(info.hasChoices) {
		if(message->leftChoice != NULL && message->leftChoice[0] != '\0') {
			choices[choicesNumber++] = LEFT_CHOICE;
		}
		if(message->middleChoice != NULL && message->middleChoice[0] != '\0') {
			choices[choicesNumber++] = MIDDLE_CHOICE;
		}
		if(message->rightChoice != NULL && message->rightChoice[0] != '\0') {
			choices[choicesNumber++] = RIGHT_CHOICE;
		}
		choices[choicesNumber] = NO_CHOICE;

		/* Find current choice number */
		for(unsigned int i = 0; i < choicesNumber; ++i) {
			if(message->currentChoice == choices[i]) {
				currentChoice = i;
				break;
			}
		}
		/* If current choice not valid, set first choice as current choice */
		if(currentChoice == 4) {
			currentChoice = 0;
			message->currentChoice = choices[currentChoice];
		}
	}
	else {
		message->currentChoice = NO_CHOICE;
	}

	/* Display message */
	drawColorMessage(&info, message, messageLines, colors);

	/* Main loop */
	cc_displayInputs(false);
	cc_setCursorVisibility(false);
	cc_Input input;
	bool exit = false;
	while(!exit) {
		input = cc_getInput();
		if(info.hasChoices) {
			switch(input.key) {
				case HOME_KEY:
					currentChoice = 0;
					break;
				case END_KEY:
					currentChoice = choicesNumber - 1;
					break;
				case LEFT_ARROW_KEY:
					if(currentChoice) {
						--currentChoice;
					}
					else {
						currentChoice = choicesNumber - 1;
					}
					break;
				case RIGHT_ARROW_KEY:
					++currentChoice;
					currentChoice %= choicesNumber;
					break;
				case ENTER_KEY:
					exit = true;
					break;
				case ESC_KEY:
					if(message->canEscape) {
						currentChoice = choicesNumber;
						exit = true;
					}
					break;
				case TAB_KEY:
					++currentChoice;
					currentChoice %= choicesNumber;
					break;
				case PAGE_UP_KEY:
				case PAGE_DOWN_KEY:
				case UP_ARROW_KEY:
				case DOWN_ARROW_KEY:
				case BACKSPACE_KEY:
				case SPACE_KEY:
				case INS_KEY:
				case DEL_KEY:
				case F1_KEY:
				case F2_KEY:
				case F3_KEY:
				case F4_KEY:
				case F5_KEY:
				case F6_KEY:
				case F7_KEY:
				case F8_KEY:
				case F9_KEY:
				case F10_KEY:
				case F11_KEY:
				case F12_KEY:
				case OTHER_KEY:
				default:
					break;
			}
			message->currentChoice = choices[currentChoice];
		}
		else {
			if(input.key == ENTER_KEY || input.key == ESC_KEY) {
				exit = true;
			}
		}

		consoleWidth = cc_getWidth();
		consoleHeight = cc_getHeight();
		if(usedWidth == consoleWidth && usedHeight == consoleHeight) {
			if(info.hasChoices) {
				drawColorMessageChoices(&info, message, colors);
			}
		}
		else {
			usedWidth = consoleWidth;
			usedHeight = consoleHeight;
			info = computeColorMessageDrawInfo(message, messageLines, linesNumber);
			drawColorMessage(&info, message, messageLines, colors);
		}
	}

	while(--linesNumber) {
		free(messageLines[linesNumber]);
	}
	free(messageLines[0]);
	free(messageLines);

	cc_setCursorPosition(nullpos);
}
