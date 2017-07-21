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

static const cc_MessageColors mcolors = {
	BLACK,
	CYAN,
	BLACK,
	WHITE,
	BLACK,
	WHITE,
	BLACK,
	CYAN,
	BLACK
};

void menuExamples() {

	const char* withColorsChoices[] = {
		"Table",
		"Color",
		"Cancel",
	};

	cc_Menu styleMenu;
	styleMenu.title = "Menu style to use";
	styleMenu.choices = withColorsChoices;
	styleMenu.choicesNumber = 3;
	styleMenu.choiceOnEscape = 2;
	styleMenu.currentChoice = 0;

	const char* choices[] = {
		"Choice 0",
		"Choice 1",
		"Choice 2"
	};

	cc_Menu menu;
	menu.title = "Menu example";
	menu.choices = choices;
	menu.choicesNumber = 3;
	menu.choiceOnEscape = 0;
	menu.currentChoice = 2;

	cc_Message choiceMessage;
	choiceMessage.title = "Choice selected";
	choiceMessage.message = NULL;
	choiceMessage.leftChoice = NULL;
	choiceMessage.middleChoice = "OK";
	choiceMessage.rightChoice = NULL;
	choiceMessage.currentChoice = NO_CHOICE;
	choiceMessage.canEscape = true;

	cc_displayColorMenu(&styleMenu, &colors);
	if(styleMenu.currentChoice == 0) {
		cc_setColors(BLACK, WHITE);
		cc_displayTableMenu(&menu);
		choiceMessage.message = choices[menu.currentChoice];
		cc_displayTableMessage(&choiceMessage);
	}
	else if(styleMenu.currentChoice == 1) {
		cc_displayColorMenu(&menu, &colors);
		choiceMessage.message = choices[menu.currentChoice];
		cc_displayColorMessage(&choiceMessage, &mcolors);
	}
}

void optionMenuExamples() {

	const char* withColorsChoices[] = {
		"Table",
		"Color",
		"Cancel",
	};

	cc_Menu styleMenu;
	styleMenu.title = "Menu style to use";
	styleMenu.choices = withColorsChoices;
	styleMenu.choicesNumber = 3;
	styleMenu.choiceOnEscape = 2;
	styleMenu.currentChoice = 0;

	cc_IntegerOption integerOption;
	integerOption.value = 42;
	integerOption.minValue = -100;
	integerOption.maxValue = 200;
	integerOption.step = 1;

	cc_Option option1;
	option1.name = "Integer option";
	option1.optionType = INTEGER_OPTION;
	option1.integerOption = &integerOption;

	cc_CharacterOption characterOption;
	characterOption.value = 'g';
	characterOption.minValue = 'a';
	characterOption.maxValue = 'z';

	cc_Option option2;
	option2.name = "Character option";
	option2.optionType = CHARACTER_OPTION;
	option2.characterOption = &characterOption;

	const char* choices[] = {"choice 1", "very very long choice", "choice 2", "choice 3"};

	cc_ChoicesOption choicesOption;
	choicesOption.choices = choices;
	choicesOption.choicesNumber = 4;
	choicesOption.currentChoice = 2;

	cc_Option option3;
	option3.name = "Choices option";
	option3.optionType = CHOICES_OPTION;
	option3.choicesOption = &choicesOption;

	cc_Option* options[] = {&option1, &option2, &option3};

	cc_OptionsMenu optionsMenu;
	optionsMenu.title = "Options menu example";
	optionsMenu.options = options;
	optionsMenu.optionsNumber = 3;
	optionsMenu.selectedOption = 0;
	optionsMenu.exitText = "OK";
	optionsMenu.hasEscaped = false;

	char messageText[256];

	cc_Message choiceMessage;
	choiceMessage.title = "Options values";
	choiceMessage.message = messageText;
	choiceMessage.leftChoice = NULL;
	choiceMessage.middleChoice = "OK";
	choiceMessage.rightChoice = NULL;
	choiceMessage.currentChoice = NO_CHOICE;
	choiceMessage.canEscape = true;

	cc_displayColorMenu(&styleMenu, &colors);
	if(styleMenu.currentChoice != 2) {
		if(styleMenu.currentChoice == 1) {
			cc_displayColorOptionMenu(&optionsMenu, &colors);
		}
		else {
			cc_setColors(BLACK, WHITE);
			cc_displayTableOptionMenu(&optionsMenu);
		}
		sprintf(messageText,
		        "Integer option value:\n%d\n\nCharacter option value:\n%c\n\nChoices option, selected option:\n%d\n(%s)",
		        integerOption.value,
		        characterOption.value,
		        choicesOption.currentChoice,
		        choices[choicesOption.currentChoice]
		);
		if(styleMenu.currentChoice == 1) {
			cc_displayColorMessage(&choiceMessage, &mcolors);
		}
		else {
			cc_displayTableMessage(&choiceMessage);
		}
	}
}

void messageExamples() {

	const char* styleChoices[] = {"Table", "Color"};
	cc_ChoicesOption styleOption;
	styleOption.choices = styleChoices;
	styleOption.choicesNumber = 2;
	styleOption.currentChoice = 0;

	cc_Option option1;
	option1.name = "Style";
	option1.optionType = CHOICES_OPTION;
	option1.choicesOption = &styleOption;

	const char* titleChoices[] = {"with", "without"};
	cc_ChoicesOption titleOption;
	titleOption.choices = titleChoices;
	titleOption.choicesNumber = 2;
	titleOption.currentChoice = 0;

	cc_Option option2;
	option2.name = "Title";
	option2.optionType = CHOICES_OPTION;
	option2.choicesOption = &titleOption;

	const char* leftChoices[] = {"yes", "no"};
	cc_ChoicesOption leftOption;
	leftOption.choices = leftChoices;
	leftOption.choicesNumber = 2;
	leftOption.currentChoice = 0;

	cc_Option option3;
	option3.name = "Left option";
	option3.optionType = CHOICES_OPTION;
	option3.choicesOption = &leftOption;

	const char* middleChoices[] = {"yes", "no"};
	cc_ChoicesOption middleOption;
	middleOption.choices = middleChoices;
	middleOption.choicesNumber = 2;
	middleOption.currentChoice = 0;

	cc_Option option4;
	option4.name = "Middle option";
	option4.optionType = CHOICES_OPTION;
	option4.choicesOption = &middleOption;

	const char* rightChoices[] = {"yes", "no"};
	cc_ChoicesOption rightOption;
	rightOption.choices = rightChoices;
	rightOption.choicesNumber = 2;
	rightOption.currentChoice = 0;

	cc_Option option5;
	option5.name = "Right option";
	option5.optionType = CHOICES_OPTION;
	option5.choicesOption = &rightOption;

	cc_Option* options[] = {&option1, &option2, &option3, &option4, &option5};

	cc_OptionsMenu optionsMenu;
	optionsMenu.title = "Options menu example";
	optionsMenu.options = options;
	optionsMenu.optionsNumber = 5;
	optionsMenu.selectedOption = 0;
	optionsMenu.exitText = "Display";
	optionsMenu.hasEscaped = false;

	cc_displayColorOptionMenu(&optionsMenu, &colors);

	if(!optionsMenu.hasEscaped) {
		cc_Message message;
		message.title = titleOption.currentChoice == 0 ? "Message title" : NULL;
		message.message = "Message text\n\n(can be multi lines)";
		message.leftChoice = leftOption.currentChoice == 0 ? "left" : NULL;
		message.middleChoice = middleOption.currentChoice == 0 ? "middle" : NULL;
		message.rightChoice = rightOption.currentChoice == 0 ? "right" : NULL;
		message.currentChoice = NO_CHOICE;
		message.canEscape = true;

		if(styleOption.currentChoice == 1) {
			cc_displayColorMessage(&message, &mcolors);
		}
		else {
			cc_setColors(BLACK, WHITE);
			cc_displayTableMessage(&message);
		}

		cc_Message choiceMessage;
		choiceMessage.title = "Message choice";
		switch(message.currentChoice) {
			case LEFT_CHOICE:
				choiceMessage.message = "LEFT_CHOICE";
				break;
			case MIDDLE_CHOICE:
				choiceMessage.message = "MIDDLE_CHOICE";
				break;
			case RIGHT_CHOICE:
				choiceMessage.message = "RIGHT_CHOICE";
				break;
			case NO_CHOICE:
			default:
				choiceMessage.message = "NO_CHOICE";
				break;
		}
		choiceMessage.leftChoice = NULL;
		choiceMessage.middleChoice = NULL;
		choiceMessage.rightChoice = NULL;
		choiceMessage.currentChoice = NO_CHOICE;
		choiceMessage.canEscape = true;

		if(styleOption.currentChoice == 1) {
			cc_displayColorMessage(&choiceMessage, &mcolors);
		}
		else {
			cc_displayTableMessage(&choiceMessage);
		}
	}
}

void UIExamples() {

	const char* choices[] = {
		"Menu examples",
		"Options menus examples",
		"Messages examples",
		"Back",
	};

	cc_Menu menu;
	menu.title = "UI examples";
	menu.choices = choices;
	menu.choicesNumber = 4;
	menu.currentChoice = 0;
	menu.choiceOnEscape = 3;

	bool loop = true;
	while(loop) {
		cc_displayColorMenu(&menu, &colors);
		cc_setColors(BLACK, WHITE);
		switch(menu.currentChoice) {
			case 0:
				menuExamples();
				break;
			case 1:
				optionMenuExamples();
				break;
			case 2:
				messageExamples();
				break;
			case 3:
				loop = false;
				break;
			default:
				break;
		}
	}
}
