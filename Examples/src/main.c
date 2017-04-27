#include <ConsoleControl.h>
#include <ConsoleControlUtility.h>
#include <ConsoleControlUI.h>
#include <BasicExamples.h>

int main() {

	const char* choices[] = {
		"Basic features",
		"UI features",
		"Exit",
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
	menu.title = "ConsoleControl Examples";
	menu.choices = choices;
	menu.choicesNumber = 3;
	menu.choiceOnEscape = 2;
	menu.currentChoice = 0;

	bool loop = true;
	while(loop) {
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice) {
			case 0:
				basicExamples();
				break;
			case 1:
				//TODO
				break;
			case 2:
				loop = false;
				break;
			default:
				break;
		}
	}
	return EXIT_SUCCESS;
}
