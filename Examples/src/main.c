#include <ConsoleControl.h>
#include <ConsoleControlUtility.h>
#include <ConsoleControlUI.h>

#include <BasicExamples.h>
#include <UIExamples.h>

static const cc_MenuColors colors = {
	BLACK,
	CYAN,
	BLACK,
	WHITE,
	BLACK,
	CYAN,
	BLACK
};

int main() {

	FILE* fp = NULL;
	if(LOGGER_ENABLED){
		fp = fopen("ConsoleControl_examples_log.txt","w");
		if(fp == NULL){
			lg_setEnabled(false);
		}
	}
	lg_setOutputStream(fp);
	LOG_INFO("ConsoleControl examples start");

	const char* choices[] = {
		"Basic features",
		"UI features",
		"Exit",
	};

	cc_Menu menu;
	menu.title = "ConsoleControl Examples";
	menu.choices = choices;
	menu.choicesNumber = 3;
	menu.choiceOnEscape = 2;
	menu.currentChoice = 0;

	LOG_INFO("Enter the main menu");
	bool loop = true;
	while(loop) {
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice) {
			case 0:
				basicExamples();
				break;
			case 1:
				UIExamples();
				break;
			case 2:
				loop = false;
				break;
			default:
				break;
		}
	}
	LOG_INFO("Exit the main menu");

	cc_setCursorVisibility(true);
	cc_displayInputs(true);
	LOG_INFO("ConsoleControl examples end");
	if(fp != NULL){
		fclose(fp);
	}
	return EXIT_SUCCESS;
}
