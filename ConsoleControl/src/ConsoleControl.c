#include <ConsoleControl.h>

#include <stdio.h>

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
