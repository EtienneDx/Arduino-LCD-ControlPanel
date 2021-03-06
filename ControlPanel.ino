// include the library code
#include "menu.h"

/******Buttons*******/
#define NEXT_BUTTON 2
#define PREV_BUTTON 4
#define MAIN_BUTTON 3

/*******Menu*********/

#define ITEM_COUNT 6
MenuItem items[ITEM_COUNT]{
	{ MENU_LABEL, "Controller"},
	{ MENU_INT, "Red(/10)", 5, 0, 10, 1 },
	{ MENU_INT, "Green(/10)", 5, 0, 10, 1 },
	{ MENU_INT, "Blue(/10)", 5, 0, 10, 1 },
	{ MENU_BUTTON, "Blink LED twice", &doubleBlink },
	{ MENU_TOGGLE, "LED 13 :" }, 
};

Menu menu(0x27, 16, 2, &items[0], ITEM_COUNT, BUTTONS_MENU, NEXT_BUTTON, PREV_BUTTON, MAIN_BUTTON);

/*******LEDs*******/
#define RED A0
#define GREEN A1
#define BLUE A2

#define OTHER 13

void setup()
{
	menu.init();
	pinMode(NEXT_BUTTON, INPUT);
	pinMode(PREV_BUTTON, INPUT);
	pinMode(MAIN_BUTTON, INPUT);

	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(OTHER, OUTPUT);
}

void loop()
{
	menu.update();//needed to check the input buttons

	analogWrite(RED, items[1].value * 1024 / 10);
	analogWrite(GREEN, items[2].value * 1024 / 10);
	analogWrite(BLUE, items[3].value * 1024 / 10);

	digitalWrite(OTHER, items[5].value);

	delay(20);
}


void doubleBlink()//just for the demo
{
	analogWrite(RED, 1024);
	analogWrite(GREEN, 1024);
	analogWrite(BLUE, 1024);
	delay(250);
	analogWrite(RED, 0);
	analogWrite(GREEN, 0);
	analogWrite(BLUE, 0);
	delay(250);
	analogWrite(RED, 1024);
	analogWrite(GREEN, 1024);
	analogWrite(BLUE, 1024);
	delay(250);
	analogWrite(RED, 0);
	analogWrite(GREEN, 0);
	analogWrite(BLUE, 0);
	delay(250);
}