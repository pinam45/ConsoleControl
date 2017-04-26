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
#include <ConsoleControlMenu.h>

void printColorTable() {
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
	bool running = true;
	cc_displayInputs(false);
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

void printLineAndRectangle() {
	cc_Vector2 topLeft = {20, 5};
	cc_Vector2 downRight = {30, 20};
	cc_displayInputs(false);
	cc_clean();
	cc_Input input = cc_getInput();
	while(input.key != ESC_KEY) {
		//cc_drawLine(topLeft, downRight, ' ');
		cc_drawFullRectangle(topLeft, downRight, ' ');
		switch(input.key) {
			case UP_ARROW_KEY:
				--downRight.y;
				break;
			case DOWN_ARROW_KEY:
				if(downRight.y < cc_getHeight() - 1)
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
			case BACKSPACE_KEY:break;
			case TAB_KEY:break;
			case ENTER_KEY:break;
			case ESC_KEY:break;
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
		downRight = cc_clamp(downRight);
		//cc_drawPatternLine(topLeft, downRight, "@#");
		cc_setForegroundColor(CYAN);
		cc_drawFullRectangle(topLeft, downRight, '*');
		cc_setForegroundColor(RED);
		cc_drawLine(topLeft, downRight, '*');
		cc_setCursorPosition(downRight);
		cc_printInPlace('#');
		input = cc_getInput();
	}
	cc_displayInputs(true);
}

void printCircle() {
	cc_Vector2 center = {60, 15};
	unsigned int radius = 0;
	cc_displayInputs(false);
	cc_clean();
	cc_Input input = cc_getInput();
	while(input.key != ESC_KEY) {
		cc_drawCircle(center,radius,' ');
		switch(input.key) {
			case UP_ARROW_KEY:
			case RIGHT_ARROW_KEY:
				++radius;
				break;
			case DOWN_ARROW_KEY:
			case LEFT_ARROW_KEY:
				if(radius){
					--radius;
				}
				break;
			default:break;
			case HOME_KEY:break;
			case END_KEY:break;
			case PAGE_UP_KEY:break;
			case PAGE_DOWN_KEY:break;
			case BACKSPACE_KEY:break;
			case TAB_KEY:break;
			case ENTER_KEY:break;
			case ESC_KEY:break;
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
		}
		cc_setForegroundColor(RED);
		cc_drawCircle(center,radius,'#');
		input = cc_getInput();
	}
}

void basicExamples() {

	const char* choices[] = {
	  "Print color table",
	  "Print inputs",
	  "Print line and rectangle",
	  "Print circle",
	  "Exit",
	};
	const cc_MenuColors colors = {
	  CYAN,
	  BLACK,
	  WHITE,
	  BLACK,
	  CYAN,
	  BLACK
	};
	cc_Menu menu;
	menu.title = "ConsoleControl tests";
	menu.choices = choices;
	menu.choicesNumber = 5;
	menu.choiceOnEscape = 4;
	menu.currentChoice = 0;

	bool loop = true;
	while(loop){
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice){
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
				printLineAndRectangle();
				break;
			case 3:
				cc_clean();
				printCircle();
				break;
			case 4:
				loop = false;
				break;
			default:break;
		}
	}
}
