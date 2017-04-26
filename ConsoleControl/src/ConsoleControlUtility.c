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

#include <ConsoleControlUtility.h>

static cc_type lerp(cc_type x0, cc_type x1, double t);

static cc_Vector2 vectlerp(cc_Vector2 v0, cc_Vector2 v1, double t);

static cc_type dist(cc_Vector2 v0, cc_Vector2 v1);

cc_type lerp(cc_type x0, cc_type x1, double t) {
	return x0 + (cc_type) lround(t * (x1 - x0));
}

cc_Vector2 vectlerp(cc_Vector2 v0, cc_Vector2 v1, double t) {
	cc_Vector2 result = {
	  lerp(v0.x, v1.x, t),
	  lerp(v0.y, v1.y, t)
	};
	return result;
}

cc_type dist(cc_Vector2 v0, cc_Vector2 v1) {
	cc_type dx = abs(v1.x - v0.x);
	cc_type dy = abs(v1.y - v0.y);
	return dx > dy ? dx : dy;
}

void cc_drawRectangle(cc_Vector2 topLeft, cc_Vector2 downRight, const char ch) {
	//orientation check
	if(topLeft.x > downRight.x) {
		cc_type tmp = topLeft.x;
		topLeft.x = downRight.x;
		downRight.x = tmp;
	}
	if(topLeft.y > downRight.y) {
		cc_type tmp = topLeft.y;
		topLeft.y = downRight.y;
		downRight.y = tmp;
	}

	//top line
	cc_setCursorPosition(topLeft);
	for(cc_type i = topLeft.x; i <= downRight.x; ++i) {
		putchar(ch);
	}

	// right and left lines
	cc_Vector2 pos;
	for(pos.y = topLeft.y + 1; pos.y < downRight.y; ++pos.y) {
		pos.x = topLeft.x;
		cc_setCursorPosition(pos);
		putchar(ch);
		pos.x = downRight.x;
		cc_setCursorPosition(pos);
		putchar(ch);
	}

	//bottom line
	pos.x = topLeft.x;
	cc_setCursorPosition(pos);
	for(cc_type i = topLeft.x; i <= downRight.x; ++i) {
		putchar(ch);
	}
}

void cc_drawTableRectangle(cc_Vector2 topLeft, cc_Vector2 downRight) {
	//orientation check
	if(topLeft.x > downRight.x) {
		cc_type tmp = topLeft.x;
		topLeft.x = downRight.x;
		downRight.x = tmp;
	}
	if(topLeft.y > downRight.y) {
		cc_type tmp = topLeft.y;
		topLeft.y = downRight.y;
		downRight.y = tmp;
	}

	//top line
	cc_setCursorPosition(topLeft);
	putchar('+');
	for(cc_type i = topLeft.x + 1; i < downRight.x; ++i) {
		putchar('-');
	}
	putchar('+');

	// right and left lines
	cc_Vector2 pos;
	for(pos.y = topLeft.y + 1; pos.y < downRight.y; ++pos.y) {
		pos.x = topLeft.x;
		cc_setCursorPosition(pos);
		putchar('|');
		pos.x = downRight.x;
		cc_setCursorPosition(pos);
		putchar('|');
	}

	//bottom line
	pos.x = topLeft.x;
	cc_setCursorPosition(pos);
	putchar('+');
	for(cc_type i = topLeft.x + 1; i < downRight.x; ++i) {
		putchar('-');
	}
	putchar('+');
}

void cc_drawFullRectangle(cc_Vector2 topLeft, cc_Vector2 downRight, const char ch) {
	//orientation check
	if(topLeft.x > downRight.x) {
		cc_type tmp = topLeft.x;
		topLeft.x = downRight.x;
		downRight.x = tmp;
	}
	if(topLeft.y > downRight.y) {
		cc_type tmp = topLeft.y;
		topLeft.y = downRight.y;
		downRight.y = tmp;
	}

	cc_Vector2 pos;
	pos.x = topLeft.x;
	for(pos.y = topLeft.y; pos.y <= downRight.y; ++pos.y) {
		cc_setCursorPosition(pos);
		for(cc_type i = topLeft.x; i <= downRight.x; ++i) {
			putchar(ch);
		}
	}
}

void cc_drawLine(cc_Vector2 from, cc_Vector2 to, const char ch) {
	cc_setCursorPosition(from);
	putchar(ch);
	cc_type n = dist(from, to);
	if(n) {
		double t;
		for(double i = 1; i <= n; ++i) {
			t = i / n;
			cc_setCursorPosition(vectlerp(from, to, t));
			putchar(ch);
		}
	}
}

void cc_drawTableHorizontalLine(cc_Vector2 from, cc_Vector2 to) {
	cc_setCursorPosition(from);
	putchar('+');
	cc_type n = dist(from, to);
	if(n) {
		double t;
		for(double i = 1; i < n; ++i) {
			t = i / n;
			cc_setCursorPosition(vectlerp(from, to, t));
			putchar('-');
		}
		cc_setCursorPosition(vectlerp(from, to, 1));
		putchar('+');
	}
}

void cc_drawTableVerticalLine(cc_Vector2 from, cc_Vector2 to) {
	cc_setCursorPosition(from);
	putchar('+');
	cc_type n = dist(from, to);
	if(n) {
		double t;
		for(double i = 1; i < n; ++i) {
			t = i / n;
			cc_setCursorPosition(vectlerp(from, to, t));
			putchar('|');
		}
		cc_setCursorPosition(vectlerp(from, to, 1));
		putchar('+');
	}
}

void cc_drawPatternLine(cc_Vector2 from, cc_Vector2 to, const char* pattern) {
	unsigned int chNumber = 0;
	cc_setCursorPosition(from);
	putchar(pattern[chNumber]);
	cc_type n = dist(from, to);
	if(n) {
		double t;
		for(double i = 1; i <= n; ++i) {
			t = i / n;
			cc_setCursorPosition(vectlerp(from, to, t));
			if(pattern[++chNumber] == '\0') {
				chNumber = 0;
			}
			putchar(pattern[chNumber]);
		}
	}
}

void cc_drawCircle(cc_Vector2 center, unsigned int radius, char ch) {
	int x = (int) radius;
	int y = 0;
	int err = 0;
	cc_Vector2 pos;

	while(x >= y) {
		pos.x = center.x + x;
		pos.y = center.y + y;
		cc_setCursorPosition(pos);
		putchar(ch);
		pos.y = center.y - y;
		cc_setCursorPosition(pos);
		putchar(ch);

		pos.x = center.x + y;
		pos.y = center.y + x;
		cc_setCursorPosition(pos);
		putchar(ch);
		pos.y = center.y - x;
		cc_setCursorPosition(pos);
		putchar(ch);

		pos.x = center.x - y;
		pos.y = center.y + x;
		cc_setCursorPosition(pos);
		putchar(ch);
		pos.y = center.y - x;
		cc_setCursorPosition(pos);
		putchar(ch);

		pos.x = center.x - x;
		pos.y = center.y + y;
		cc_setCursorPosition(pos);
		putchar(ch);
		pos.y = center.y - y;
		cc_setCursorPosition(pos);
		putchar(ch);

		if(err <= 0) {
			++y;
			err += 2 * y + 1;
		}
		if(err > 0) {
			--x;
			err -= 2 * x + 1;
		}
	}
}

void cc_displayTableMenu(cc_Menu* menu) {
	unsigned int maxLength = (unsigned int) strlen(menu->title);
	unsigned int len;
	/* Compute maxLength */
	for(unsigned int i = menu->choicesNumber; i--;) {
		len = (unsigned int) strlen(menu->choices[i]);
		if(len > maxLength) {
			maxLength = len;
		}
	}

	unsigned int width = maxLength + 7;
	unsigned int height = menu->choicesNumber * 2 + 6;

	cc_Vector2 topLeft = { // topLeft for the title
	  (cc_getWidth() - (cc_type) width) / 2,
	  (cc_getHeight() - (cc_type) height) / 2
	};
	cc_Vector2 downRight = { // downRight for the title
	  topLeft.x + (cc_type) width,
	  topLeft.y + (cc_type) height
	};

	/* Print the title */
	cc_clean();
	cc_drawTableRectangle(topLeft, downRight);
	topLeft.y += 2;
	cc_Vector2 pos = {
	  topLeft.x + (cc_type) (width - (unsigned int) strlen(menu->title)) / 2 + 1,
	  topLeft.y
	};
	cc_setCursorPosition(pos);
	printf("%s", menu->title);
	topLeft.y += 2; // topleft is now for the choices
	cc_Vector2 topright = { // topright for the choices
	  downRight.x,
	  topLeft.y
	};
	cc_drawTableHorizontalLine(topLeft, topright);

	/* Print the choices */
	for(unsigned int i = menu->choicesNumber; i--;) {
		pos.x = topLeft.x + (cc_type) (width - (unsigned int) strlen(menu->choices[i])) / 2 - 1;
		pos.y = topLeft.y + (cc_type) (2 * (i + 1));
		cc_setCursorPosition(pos);
		if(menu->currentChoice == i) {
			printf("> %s <", menu->choices[i]);
		}
		else {
			printf("  %s  ", menu->choices[i]);
		}
	}
	cc_Vector2 nullpos = {0, 0};
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

		/* Print the choices */
		for(unsigned int i = menu->choicesNumber; i--;) {
			pos.x = topLeft.x + (cc_type) (width - (unsigned int) strlen(menu->choices[i])) / 2 - 1;
			pos.y = topLeft.y + (cc_type) (2 * (i + 1));
			cc_setCursorPosition(pos);
			if(menu->currentChoice == i) {
				printf("> %s <", menu->choices[i]);
			}
			else {
				printf("  %s  ", menu->choices[i]);
			}
		}
		cc_setCursorPosition(nullpos);
	}
}

void cc_displayColorMenu(cc_Menu* menu, const cc_MenuColors* colors) {
	unsigned int maxLength = (unsigned int) strlen(menu->title);
	unsigned int len;
	/* Compute maxLength */
	for(unsigned int i = menu->choicesNumber; i--;) {
		len = (unsigned int) strlen(menu->choices[i]);
		if(len > maxLength) {
			maxLength = len;
		}
	}

	unsigned int width = maxLength + 5;
	unsigned int height = menu->choicesNumber * 2 + 5;

	cc_Vector2 topLeft = { // topLeft for the title
	  (cc_getWidth() - (cc_type) width) / 2,
	  (cc_getHeight() - (cc_type) height) / 2
	};
	cc_Vector2 downRight = { // downRight for the title
	  topLeft.x + (cc_type) width,
	  topLeft.y + 3
	};

	/* Print the title */
	cc_clean();
	cc_setColors(colors->titleBackgroundColor, colors->titleForegroundColor);
	cc_drawFullRectangle(topLeft, downRight, ' ');
	++topLeft.y;
	cc_Vector2 pos = {
	  topLeft.x + (cc_type) (width - (unsigned int) strlen(menu->title)) / 2 + 1,
	  topLeft.y
	};
	cc_setCursorPosition(pos);
	printf("%s", menu->title);

	/* If same backgroud color for title and choices, draw a line */
	if(colors->titleBackgroundColor == colors->backgroundColor) {
		++topLeft.y;
		--downRight.y;
		cc_drawLine(topLeft, downRight, '_');
		++topLeft.y;
	}
	else {
		topLeft.y += 2;
	}
	// topleft is now for the choices background

	downRight.y = topLeft.y + (cc_type) height - 5; // downRight for the choices
	cc_setColors(colors->backgroundColor, colors->foregroundColor);
	cc_drawFullRectangle(topLeft, downRight, ' ');
	++topLeft.y; // topleft is now for the first choices y coordinate

	/* Print the choices */
	pos.x = topLeft.x + 1;
	for(unsigned int i = menu->choicesNumber; i--;) {
		pos.y = topLeft.y + (cc_type) (2 * i);
		cc_setCursorPosition(pos);
		if(menu->currentChoice == i) {
			cc_setColors(colors->selectionBackgroundColor, colors->selectionForegroundColor);
		}
		unsigned j = 0;
		for(; j < (width - (unsigned int) strlen(menu->choices[i])) / 2; ++j) {
			putchar(' ');
		}
		printf("%s", menu->choices[i]);
		j += (unsigned int) strlen(menu->choices[i]);
		for(; j < width - 1; ++j) {
			putchar(' ');
		}
		if(menu->currentChoice == i) {
			cc_setColors(colors->backgroundColor, colors->foregroundColor);
		}
	}
	cc_Vector2 nullpos = {0, 0};
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

		/* Print the choices */
		for(unsigned int i = menu->choicesNumber; i--;) {
			pos.y = topLeft.y + (cc_type) (2 * i);
			cc_setCursorPosition(pos);
			if(menu->currentChoice == i) {
				cc_setColors(colors->selectionBackgroundColor, colors->selectionForegroundColor);
			}
			unsigned j = 0;
			for(; j < (width - (unsigned int) strlen(menu->choices[i])) / 2; ++j) {
				putchar(' ');
			}
			printf("%s", menu->choices[i]);
			j += (unsigned int) strlen(menu->choices[i]);
			for(; j < width - 1; ++j) {
				putchar(' ');
			}
			if(menu->currentChoice == i) {
				cc_setColors(colors->backgroundColor, colors->foregroundColor);
			}
		}
		cc_setCursorPosition(nullpos);
	}
}
