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

void printColorTable() {
	LOG_INFO("Print color table");

	cc_displayInputs(false);
	cc_setBackgroundColor(BLACK);
	cc_clean();

	cc_Color colors[] = {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		YELLOW,
		WHITE,
		LIGHT_BLACK,
		LIGHT_BLUE,
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_RED,
		LIGHT_MAGENTA,
		LIGHT_YELLOW,
		LIGHT_WHITE
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
	cc_setColors(BLACK, WHITE);
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
		cc_setColors(BLACK, WHITE);
		printf("|%s|", colorNames[i]);
		cc_setForegroundColor(colors[i]);
		for(unsigned int j = 0; j < 8; ++j) {
			cc_setBackgroundColor(colors[j]);
			printf("   sample   ");
		}
		cc_setColors(BLACK, WHITE);
		printf("|\n");
	}
	cc_setColors(BLACK, WHITE);
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
		cc_setColors(BLACK, WHITE);
		printf("|%s|", colorNames[i]);
		cc_setForegroundColor(colors[i]);
		for(unsigned int j = 8; j < 16; ++j) {
			cc_setBackgroundColor(colors[j]);
			printf("   sample   ");
		}
		cc_setColors(BLACK, WHITE);
		printf("|\n");
	}
	cc_setColors(BLACK, WHITE);
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

void printInputs() {
	LOG_INFO("Print inputs");

	cc_displayInputs(false);
	cc_setBackgroundColor(BLACK);
	cc_clean();

	bool running = true;
	while(running) {
		cc_Input input = cc_getInput();
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

void printLines() {
	LOG_INFO("Print lines");

	cc_Vector2 topLeft = {0, 0};
	cc_Vector2 topRight = {cc_getWidth() - 2, 0};
	cc_Vector2 downLeft = {0, cc_getHeight() - 1};
	cc_Vector2 downRight = {topRight.x, downLeft.y};
	cc_Vector2 pos = {cc_getWidth() / 2, cc_getHeight() / 2};
	cc_displayInputs(false);
	cc_setBackgroundColor(BLACK);
	cc_clean();

	cc_setForegroundColor(GREEN);
	cc_drawLine(topLeft, pos, '*');
	cc_setForegroundColor(CYAN);
	cc_drawLine(topRight, pos, '*');
	cc_setForegroundColor(MAGENTA);
	cc_drawLine(downLeft, pos, '*');
	cc_setForegroundColor(YELLOW);
	cc_drawLine(downRight, pos, '*');
	cc_setForegroundColor(WHITE);
	cc_setCursorPosition(pos);
	cc_printInPlace('#');
	cc_Input input = cc_getInput();
	while(input.key != ESC_KEY) {
		cc_drawLine(topLeft, pos, ' ');
		cc_drawLine(topRight, pos, ' ');
		cc_drawLine(downLeft, pos, ' ');
		cc_drawLine(downRight, pos, ' ');

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
				if(pos.x < cc_getWidth() - 2)
					++pos.x;
				break;
			case HOME_KEY:
				pos.x = 0;
				break;
			case END_KEY:
				pos.x = cc_getWidth() - 2;
				break;
			case PAGE_UP_KEY:
				pos.y = 0;
				break;
			case PAGE_DOWN_KEY:
				pos.y = cc_getHeight() - 1;
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
		topRight.x = cc_getWidth() - 2;
		downLeft.y = cc_getHeight() - 1;
		downRight.x = topRight.x;
		downRight.y = downLeft.y;
		pos = cc_clamp(pos);

		cc_setForegroundColor(GREEN);
		cc_drawLine(topLeft, pos, '*');
		cc_setForegroundColor(CYAN);
		cc_drawLine(topRight, pos, '*');
		cc_setForegroundColor(MAGENTA);
		cc_drawLine(downLeft, pos, '*');
		cc_setForegroundColor(YELLOW);
		cc_drawLine(downRight, pos, '*');
		cc_setForegroundColor(WHITE);
		cc_setCursorPosition(pos);
		cc_printInPlace('#');

		input = cc_getInput();
	}
}

void printRectangles() {
	LOG_INFO("Print rectangles");

	cc_Vector2 topLeft = {20, 5};
	cc_Vector2 downRight = {30, 20};
	cc_displayInputs(false);
	cc_setBackgroundColor(BLACK);
	cc_clean();

	cc_setForegroundColor(CYAN);
	cc_drawFullRectangle(topLeft, downRight, '*');
	cc_setForegroundColor(GREEN);
	cc_drawRectangle(topLeft, downRight, '+');
	cc_setForegroundColor(WHITE);
	cc_setCursorPosition(downRight);
	cc_printInPlace('#');

	cc_Input input = cc_getInput();
	while(input.key != ESC_KEY) {
		cc_drawFullRectangle(topLeft, downRight, ' ');
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
				if(downRight.x < cc_getWidth() - 2)
					++downRight.x;
				break;
			case HOME_KEY:
				downRight.x = 0;
				break;
			case END_KEY:
				downRight.x = cc_getWidth() - 2;
				break;
			case PAGE_UP_KEY:
				downRight.y = 0;
				break;
			case PAGE_DOWN_KEY:
				downRight.y = cc_getHeight() - 1;
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

		downRight = cc_clamp(downRight);
		cc_setForegroundColor(CYAN);
		cc_drawFullRectangle(topLeft, downRight, '*');
		cc_setForegroundColor(GREEN);
		cc_drawRectangle(topLeft, downRight, '+');
		cc_setForegroundColor(WHITE);
		cc_setCursorPosition(downRight);
		cc_printInPlace('#');
		input = cc_getInput();
	}
}

void printCircle() {
	LOG_INFO("Print circle");

	cc_displayInputs(false);
	cc_setBackgroundColor(BLACK);
	cc_clean();

	cc_Vector2 center = {cc_getWidth() / 2, cc_getHeight() / 2};
	unsigned int radius = 5;

	cc_setForegroundColor(GREEN);
	cc_drawCircle(center, radius, '#');
	cc_setForegroundColor(WHITE);
	cc_setCursorPosition(center);
	putchar('#');

	cc_Input input = cc_getInput();
	while(input.key != ESC_KEY) {
		cc_drawCircle(center, radius, ' ');
		cc_setCursorPosition(center);
		putchar(' ');
		center.x = cc_getWidth() / 2;
		center.y = cc_getHeight() / 2;
		switch(input.key) {
			case UP_ARROW_KEY:
			case RIGHT_ARROW_KEY:
				if((unsigned int) (center.x) + radius < (unsigned int) (cc_getWidth() - 1)
				   && (unsigned int) (center.y) + radius < (unsigned int) (cc_getHeight() - 1)) {
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

		cc_setForegroundColor(GREEN);
		cc_drawCircle(center, radius, '#');
		cc_setForegroundColor(WHITE);
		cc_setCursorPosition(center);
		putchar('#');
		input = cc_getInput();
	}
}

void basicExamples() {

	const char* choices[] = {
		"Print color table",
		"Print inputs",
		"Print lines",
		"Print rectangles",
		"Print circle",
		"Back",
	};
	const cc_MenuColors colors = {
		BLACK,
		CYAN,
		BLACK,
		WHITE,
		BLACK,
		CYAN,
		BLACK
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
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice) {
			case 0:
				cc_clean();
				printColorTable();
				cc_getInput();
				break;
			case 1:
				cc_clean();
				printInputs();
				break;
			case 2:
				cc_clean();
				printLines();
				break;
			case 3:
				cc_clean();
				printRectangles();
				break;
			case 4:
				cc_clean();
				printCircle();
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
