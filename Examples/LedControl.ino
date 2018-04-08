/*
* Example for the use of the menu 'library' :
*
* This example simply allow to control the led 13
*
* connections :
* pin 2 -> "Next" Button
* pin 3 -> "Main" Button
* pin 4 -> "Previous" Button
* pin 13 -> LED (built-in on most boards)
*
*/
#include "menu.h"

#define NEXT_BUTTON 2
#define PREV_BUTTON 4
#define MAIN_BUTTON 3

#define COUNT 2

MenuItem items[COUNT] = {
	{MENU_LABEL, "LED LCD controller"},
	{MENU_TOGGLE, "LED 13 :"}
};

Menu menu(0x27, 16, 2, &items[0], COUNT, BUTTONS_MENU, NEXT_BUTTON, PREV_BUTTON, MAIN_BUTTON);

void setup()
{
	menu.init();//init the lcd
  pinMode(13, OUTPUT);
}

void loop()
{
	menu.update();//refresh the display
	digitalWrite(13, items[1].value);//we simply write the value of the toggle item to the led
	delay(20);
}
