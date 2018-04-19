#include <log.h>
#include <ConsoleControl.h>
#include <ConsoleControlUtility.h>
#include <ConsoleControlUI.h>

#include <BasicExamples.h>
#include <UIExamples.h>

#include <stdio.h>
#include <stdlib.h>

static const cc_MenuColors colors = {
	CC_BLACK,
	CC_CYAN,
	CC_BLACK,
	CC_WHITE,
	CC_BLACK,
	CC_CYAN,
	CC_BLACK
};

int main() {

	cc_Handle cch = cc_start();

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
		cc_displayColorMenu(cch, &menu, &colors);
		cc_setColors(cch, CC_BLACK, CC_WHITE);
		switch(menu.currentChoice) {
			case 0:
				basicExamples(cch);
				break;
			case 1:
				UIExamples(cch);
				break;
			case 2:
				loop = false;
				break;
			default:
				break;
		}
	}
	LOG_INFO("Exit the main menu");

	cc_setCursorVisibility(cch, true);
	cc_displayInputs(cch, true);
	LOG_INFO("ConsoleControl examples end");
	if(fp != NULL){
		fclose(fp);
	}
	return EXIT_SUCCESS;
}
