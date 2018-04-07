#include "menu.h"

MenuItem::MenuItem(char itemType, char *text, int value, int min, int max, int step) : 
	itemType(itemType), text(text), value(value), _min(min), _max(max), step(step) {}
MenuItem::MenuItem(char itemType, char *text) : 
	itemType(itemType), text(text), value(0), _min(0), _max(0), step(1) {}
MenuItem::MenuItem(char itemType, char *text, void(*callback)()) : 
	itemType(itemType), text(text), value(0), _min(0), _max(0), step(1), callback(callback) {}


Menu::Menu(int adress, int col, int row, MenuItem *fItem, int length) :
		lcd(adress, col, row), row(row), firstItem(fItem), length(length)
{
	actualLine = 0;
	actualShift = 0;
	selected = 0;
	enabled = 1;
}

void Menu::init()// called in setup
{
	lcd.init();
	lcd.backlight();

	display();
}

void Menu::display() // called to refresh the lcd
{
	if (!enabled)return;// only if enabled
	lcd.clear();
	if (!selected)// nothing selected
	{
		lcd.setCursor(0, actualLine);
		lcd.print(">");
		for (int i = 0; i < row && actualShift + i < length; i++)// for each row with some content
		{
			lcd.setCursor(1, i);
			lcd.print((firstItem + actualShift + i)->text);
			// display the value
			if ((firstItem + actualShift + i)->itemType == MENU_INT)
			{
				lcd.print(" ");
				lcd.print((firstItem + actualShift + i)->value);
			}
			else if ((firstItem + actualShift + i)->itemType == MENU_TOGGLE)
			{
				lcd.print(" ");
				lcd.print((firstItem + actualShift + i)->value ? "On" : "Off");
			}
		}
	}
	else// something selected
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print((firstItem + actualShift + actualLine)->text);
		lcd.setCursor(4, 1);
		lcd.print((firstItem + actualShift + actualLine)->value);
	}
}

void Menu::nextLine()
{
	if (!enabled)return;
	if (selected)// if something is selected, we change it's value
	{
		changeVal(1);
	}
	else if (actualLine + actualShift + 1 < length)// if next line exists
	{
		if (actualLine + 1 < row)// if we're not on the last line of the display
		{
			actualLine++;// the arrow goes down
		}
		else
		{
			actualShift++;// all the lines move up
		}
	}
	display();
}

void Menu::prevLine()
{
	if (!enabled)return;
	if (selected)// anything selected
	{
		changeVal(-1);
	}
	else if (actualLine + actualShift > 0)// if prev line exists
	{
		if (actualLine > 0)// if we're not on the first line of the display
		{
			actualLine--;// arrow goes up
		}
		else
		{
			actualShift--;// all lines go down
		}
	}
	display();
}

void Menu::selectLine()// select button got pressed
{
	if (!enabled)return;
	int type = (firstItem + actualShift + actualLine)->itemType;
	if (selected)//if something was selected, we unselect it
	{
		selected = 0;
	}
	else if (type == MENU_INT)// if int, we select it
	{
		selected = 1;
	}
	else if (type == MENU_BUTTON)// if button, we call the callback
	{
		(firstItem + actualShift + actualLine)->callback();
	}
	else if (type == MENU_TOGGLE)// if toggle, we toggle the value
	{
		(firstItem + actualShift + actualLine)->value = !(firstItem + actualShift + actualLine)->value;
	}
	display();
}

void Menu::changeVal(int v)// if something is selected, the next and prev will change this
{
	if (!enabled)return;
	(firstItem + actualShift + actualLine)->value += v * (firstItem + actualShift + actualLine)->step;
	// we need to keep it in the limits
	if ((firstItem + actualShift + actualLine)->value > (firstItem + actualShift + actualLine)->_max)
		(firstItem + actualShift + actualLine)->value = (firstItem + actualShift + actualLine)->_max;
	if ((firstItem + actualShift + actualLine)->value < (firstItem + actualShift + actualLine)->_min)
		(firstItem + actualShift + actualLine)->value = (firstItem + actualShift + actualLine)->_min;
}

void Menu::disable()
{
	enabled = 0;
}
void Menu::enable()
{
	enabled = 1;
}