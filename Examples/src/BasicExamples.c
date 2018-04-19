/*****************************************************************************************
 *                                                                                       *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2016 Maxime Pinard                                                      *
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

#include <BasicExamples.h>

#include <log.h>

void printColorTable(cc_Handle cch) {
	LOG_INFO("Print color table");

	cc_displayInputs(cch, false);
	cc_setBackgroundColor(cch, CC_BLACK);
	cc_clean(cch);

	cc_Color colors[] = {
		CC_BLACK,
		CC_BLUE,
		CC_GREEN,
		CC_CYAN,
		CC_RED,
		CC_MAGENTA,
		CC_YELLOW,
		CC_WHITE,
		CC_LIGHT_BLACK,
		CC_LIGHT_BLUE,
		CC_LIGHT_GREEN,
		CC_LIGHT_CYAN,
		CC_LIGHT_RED,
		CC_LIGHT_MAGENTA,
		CC_LIGHT_YELLOW,
		CC_LIGHT_WHITE
	};
	char colorNames[][20] = {
		"BLACK         ",
		"BLUE          ",
		"GREEN         ",
		"CYAN          ",
		"RED           ",
		"MAGENTA       ",
		"YELLOW        ",
		"WHITE         ",
		"LIGHT_BLACK   ",
		"LIGHT_BLUE    ",
		"LIGHT_GREEN   ",
		"LIGHT_CYAN    ",
		"LIGHT_RED     ",
		"LIGHT_MAGENTA ",
		"LIGHT_YELLOW  ",
		"LIGHT_WHITE   "
	};
	cc_setColors(cch, CC_BLACK, CC_WHITE);
	printf("+");
	for(unsigned int a = 15; --a;) {
		printf("-");
	}
	printf("+");
	for(unsigned int a = 97; --a;) {
		printf("-");
	}
	printf("+");
	printf("\n");
	for(unsigned int i = 0; i < 16; ++i) {
		cc_setColors(cch, CC_BLACK, CC_WHITE);
		printf("|%s|", colorNames[i]);
		cc_setForegroundColor(cch, colors[i]);
		for(unsigned int j = 0; j < 8; ++j) {
			cc_setBackgroundColor(cch, colors[j]);
			printf("   sample   ");
		}
		cc_setColors(cch, CC_BLACK, CC_WHITE);
		printf("|\n");
	}
	cc_setColors(cch, CC_BLACK, CC_WHITE);
	printf("+");
	for(unsigned int a = 15; --a;) {
		printf("-");
	}
	printf("+");
	for(unsigned int a = 97; --a;) {
		printf("-");
	}
	printf("+");
	printf("\n");
	for(unsigned int i = 0; i < 16; ++i) {
		cc_setColors(cch, CC_BLACK, CC_WHITE);
		printf("|%s|", colorNames[i]);
		cc_setForegroundColor(cch, colors[i]);
		for(unsigned int j = 8; j < 16; ++j) {
			cc_setBackgroundColor(cch, colors[j]);
			printf("   sample   ");
		}
		cc_setColors(cch, CC_BLACK, CC_WHITE);
		printf("|\n");
	}
	cc_setColors(cch, CC_BLACK, CC_WHITE);
	printf("+");
	for(unsigned int a = 15; --a;) {
		printf("-");
	}
	printf("+");
	for(unsigned int a = 97; --a;) {
		printf("-");
	}
	printf("+");
	printf("\n");
}

void printInputs(cc_Handle cch) {
	LOG_INFO("Print inputs");

	cc_displayInputs(cch, false);
	cc_setBackgroundColor(cch, CC_BLACK);
	cc_clean(cch);

	bool running = true;
	while(running) {
		cc_Input input = cc_getInput(cch);
		switch(input.key) {
			case HOME_KEY:
				printf(" >> HOME_KEY");
				break;
			case END_KEY:
				printf(" >> END_KEY");
				break;
			case PAGE_UP_KEY:
				printf(" >> PAGE_UP_KEY");
				break;
			case PAGE_DOWN_KEY:
				printf(" >> PAGE_DOWN_KEY");
				break;
			case UP_ARROW_KEY:
				printf(" >> UP_ARROW_KEY");
				break;
			case DOWN_ARROW_KEY:
				printf(" >> DOWN_ARROW_KEY");
				break;
			case LEFT_ARROW_KEY:
				printf(" >> LEFT_ARROW_KEY");
				break;
			case RIGHT_ARROW_KEY:
				printf(" >> RIGHT_ARROW_KEY");
				break;
			case BACKSPACE_KEY:
				printf(" >> BACKSPACE_KEY");
				break;
			case TAB_KEY:
				printf(" >> TAB_KEY");
				break;
			case ENTER_KEY:
				printf(" >> ENTER_KEY");
				break;
			case ESC_KEY:
				printf(" >> ESC_KEY");
				running = false;
				break;
			case SPACE_KEY:
				printf(" >> SPACE_KEY");
				break;
			case INS_KEY:
				printf(" >> INS_KEY");
				break;
			case DEL_KEY:
				printf(" >> DEL_KEY");
				break;
			case F1_KEY:
				printf(" >> F1_KEY");
				break;
			case F2_KEY:
				printf(" >> F2_KEY");
				break;
			case F3_KEY:
				printf(" >> F3_KEY");
				break;
			case F4_KEY:
				printf(" >> F4_KEY");
				break;
			case F5_KEY:
				printf(" >> F5_KEY");
				break;
			case F6_KEY:
				printf(" >> F6_KEY");
				break;
			case F7_KEY:
				printf(" >> F7_KEY");
				break;
			case F8_KEY:
				printf(" >> F8_KEY");
				break;
			case F9_KEY:
				printf(" >> F9_KEY");
				break;
			case F10_KEY:
				printf(" >> F10_KEY");
				break;
			case F11_KEY:
				printf(" >> F11_KEY");
				break;
			case F12_KEY:
				printf(" >> F12_KEY");
				break;
			default:
			case OTHER_KEY:
				printf(" >> OTHER_KEY");
				break;
		}
		printf(" >> (%d)", input.ch);
		printf("\n");
	}
}

void printLines(cc_Handle cch) {
	LOG_INFO("Print lines");

	cc_Vector2 topLeft = {0, 0};
	cc_Vector2 topRight = {cc_getWidth(cch) - 2, 0};
	cc_Vector2 downLeft = {0, cc_getHeight(cch) - 1};
	cc_Vector2 downRight = {topRight.x, downLeft.y};
	cc_Vector2 pos = {cc_getWidth(cch) / 2, cc_getHeight(cch) / 2};
	cc_displayInputs(cch, false);
	cc_setBackgroundColor(cch, CC_BLACK);
	cc_clean(cch);

	cc_setForegroundColor(cch, CC_GREEN);
	cc_drawLine(cch, topLeft, pos, '*');
	cc_setForegroundColor(cch, CC_CYAN);
	cc_drawLine(cch, topRight, pos, '*');
	cc_setForegroundColor(cch, CC_MAGENTA);
	cc_drawLine(cch, downLeft, pos, '*');
	cc_setForegroundColor(cch, CC_YELLOW);
	cc_drawLine(cch, downRight, pos, '*');
	cc_setForegroundColor(cch, CC_WHITE);
	cc_setCursorPosition(cch, pos);
	cc_printInPlace(cch, '#');
	cc_Input input = cc_getInput(cch);
	while(input.key != ESC_KEY) {
		cc_drawLine(cch, topLeft, pos, ' ');
		cc_drawLine(cch, topRight, pos, ' ');
		cc_drawLine(cch, downLeft, pos, ' ');
		cc_drawLine(cch, downRight, pos, ' ');

		switch(input.key) {
			case UP_ARROW_KEY:
				--pos.y;
				break;
			case DOWN_ARROW_KEY:
				++pos.y;
				break;
			case LEFT_ARROW_KEY:
				--pos.x;
				break;
			case RIGHT_ARROW_KEY:
				if(pos.x < cc_getWidth(cch) - 2)
					++pos.x;
				break;
			case HOME_KEY:
				pos.x = 0;
				break;
			case END_KEY:
				pos.x = cc_getWidth(cch) - 2;
				break;
			case PAGE_UP_KEY:
				pos.y = 0;
				break;
			case PAGE_DOWN_KEY:
				pos.y = cc_getHeight(cch) - 1;
				break;
			case BACKSPACE_KEY:
			case TAB_KEY:
			case ENTER_KEY:
			case ESC_KEY:
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
		topRight.x = cc_getWidth(cch) - 2;
		downLeft.y = cc_getHeight(cch) - 1;
		downRight.x = topRight.x;
		downRight.y = downLeft.y;
		pos = cc_clamp(cch, pos);

		cc_setForegroundColor(cch, CC_GREEN);
		cc_drawLine(cch, topLeft, pos, '*');
		cc_setForegroundColor(cch, CC_CYAN);
		cc_drawLine(cch, topRight, pos, '*');
		cc_setForegroundColor(cch, CC_MAGENTA);
		cc_drawLine(cch, downLeft, pos, '*');
		cc_setForegroundColor(cch, CC_YELLOW);
		cc_drawLine(cch, downRight, pos, '*');
		cc_setForegroundColor(cch, CC_WHITE);
		cc_setCursorPosition(cch, pos);
		cc_printInPlace(cch, '#');

		input = cc_getInput(cch);
	}
}

void printRectangles(cc_Handle cch) {
	LOG_INFO("Print rectangles");

	cc_Vector2 topLeft = {20, 5};
	cc_Vector2 downRight = {30, 20};
	cc_displayInputs(cch, false);
	cc_setBackgroundColor(cch, CC_BLACK);
	cc_clean(cch);

	cc_setForegroundColor(cch, CC_CYAN);
	cc_drawFullRectangle(cch, topLeft, downRight, '*');
	cc_setForegroundColor(cch, CC_GREEN);
	cc_drawRectangle(cch, topLeft, downRight, '+');
	cc_setForegroundColor(cch, CC_WHITE);
	cc_setCursorPosition(cch, downRight);
	cc_printInPlace(cch, '#');

	cc_Input input = cc_getInput(cch);
	while(input.key != ESC_KEY) {
		cc_drawFullRectangle(cch, topLeft, downRight, ' ');
		switch(input.key) {
			case UP_ARROW_KEY:
				--downRight.y;
				break;
			case DOWN_ARROW_KEY:
				++downRight.y;
				break;
			case LEFT_ARROW_KEY:
				--downRight.x;
				break;
			case RIGHT_ARROW_KEY:
				if(downRight.x < cc_getWidth(cch) - 2)
					++downRight.x;
				break;
			case HOME_KEY:
				downRight.x = 0;
				break;
			case END_KEY:
				downRight.x = cc_getWidth(cch) - 2;
				break;
			case PAGE_UP_KEY:
				downRight.y = 0;
				break;
			case PAGE_DOWN_KEY:
				downRight.y = cc_getHeight(cch) - 1;
				break;
			case BACKSPACE_KEY:
			case TAB_KEY:
			case ENTER_KEY:
			case ESC_KEY:
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

		downRight = cc_clamp(cch, downRight);
		cc_setForegroundColor(cch, CC_CYAN);
		cc_drawFullRectangle(cch, topLeft, downRight, '*');
		cc_setForegroundColor(cch, CC_GREEN);
		cc_drawRectangle(cch, topLeft, downRight, '+');
		cc_setForegroundColor(cch, CC_WHITE);
		cc_setCursorPosition(cch, downRight);
		cc_printInPlace(cch, '#');
		input = cc_getInput(cch);
	}
}

void printCircle(cc_Handle cch) {
	LOG_INFO("Print circle");

	cc_displayInputs(cch, false);
	cc_setBackgroundColor(cch, CC_BLACK);
	cc_clean(cch);

	cc_Vector2 center = {cc_getWidth(cch) / 2, cc_getHeight(cch) / 2};
	unsigned int radius = 5;

	cc_setForegroundColor(cch, CC_GREEN);
	cc_drawCircle(cch, center, radius, '#');
	cc_setForegroundColor(cch, CC_WHITE);
	cc_setCursorPosition(cch, center);
	putchar('#');

	cc_Input input = cc_getInput(cch);
	while(input.key != ESC_KEY) {
		cc_drawCircle(cch, center, radius, ' ');
		cc_setCursorPosition(cch, center);
		putchar(' ');
		center.x = cc_getWidth(cch) / 2;
		center.y = cc_getHeight(cch) / 2;
		switch(input.key) {
			case UP_ARROW_KEY:
			case RIGHT_ARROW_KEY:
				if((unsigned int) (center.x) + radius < (unsigned int) (cc_getWidth(cch) - 1)
				   && (unsigned int) (center.y) + radius < (unsigned int) (cc_getHeight(cch) - 1)) {
					++radius;
				}
				break;
			case DOWN_ARROW_KEY:
			case LEFT_ARROW_KEY:
				if(radius) {
					--radius;
				}
				break;
			case HOME_KEY:
			case END_KEY:
			case PAGE_UP_KEY:
			case PAGE_DOWN_KEY:
			case BACKSPACE_KEY:
			case TAB_KEY:
			case ENTER_KEY:
			case ESC_KEY:
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

		cc_setForegroundColor(cch, CC_GREEN);
		cc_drawCircle(cch, center, radius, '#');
		cc_setForegroundColor(cch, CC_WHITE);
		cc_setCursorPosition(cch, center);
		putchar('#');
		input = cc_getInput(cch);
	}
}

void basicExamples(cc_Handle cch) {

	const char* choices[] = {
		"Print color table",
		"Print inputs",
		"Print lines",
		"Print rectangles",
		"Print circle",
		"Back",
	};
	const cc_MenuColors colors = {
		CC_BLACK,
		CC_CYAN,
		CC_BLACK,
		CC_WHITE,
		CC_BLACK,
		CC_CYAN,
		CC_BLACK
	};
	cc_Menu menu;
	menu.title = "Basic examples";
	menu.choices = choices;
	menu.choicesNumber = 6;
	menu.currentChoice = 0;
	menu.choiceOnEscape = 5;

	LOG_INFO("Enter the basic examples menu");
	bool loop = true;
	while(loop) {
		cc_displayColorMenu(cch, &menu, &colors);
		cc_setColors(cch, CC_BLACK, CC_WHITE);
		switch(menu.currentChoice) {
			case 0:
				cc_clean(cch);
				printColorTable(cch);
				cc_getInput(cch);
				break;
			case 1:
				cc_clean(cch);
				printInputs(cch);
				break;
			case 2:
				cc_clean(cch);
				printLines(cch);
				break;
			case 3:
				cc_clean(cch);
				printRectangles(cch);
				break;
			case 4:
				cc_clean(cch);
				printCircle(cch);
				break;
			case 5:
				loop = false;
				break;
			default:
				break;
		}
	}
	LOG_INFO("Exit the basic examples menu");
}
