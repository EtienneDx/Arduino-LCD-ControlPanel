#include "menu.h"

MenuItem::MenuItem(char itemType, char *text, int value, int min, int max) : 
	itemType(itemType), text(text), value(value), _min(min), _max(max) {}
MenuItem::MenuItem(char itemType, char *text) : 
	itemType(itemType), text(text), value(0), _min(0), _max(0) {}
MenuItem::MenuItem(char itemType, char *text, void(*callback)()) : 
	itemType(itemType), text(text), value(0), _min(0), _max(0), callback(callback) {}


Menu::Menu(int adress, int col, int row, MenuItem *fItem, int length) :
		lcd(adress, col, row), row(row), firstItem(fItem), length(length)
{
	actualLine = 0;
	actualShift = 0;
	selected = 0;
	enabled = 1;
}

void Menu::init()
{
	lcd.init();
	lcd.backlight();

	display();
}

void Menu::display() 
{
	if (!enabled)return;
	lcd.clear();
	if (!selected)
	{
		lcd.setCursor(0, actualLine);
		lcd.print(">");
		for (int i = 0; i < row && actualShift + i < length; i++)// for each row with some content
		{
			lcd.setCursor(1, i);
			lcd.print((firstItem + actualShift + i)->text);
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
	else
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
	if (selected)
	{
		changeVal(1);
	}
	else if (actualLine + actualShift + 1 < length)// if next line exists
	{
		if (actualLine + 1 < row)// if we're not on the last line of the display
		{
			actualLine++;
		}
		else
		{
			actualShift++;
		}
	}
	display();
}

void Menu::prevLine()
{
	if (!enabled)return;
	if (selected)
	{
		changeVal(-1);
	}
	else if (actualLine + actualShift > 0)// if prev line exists
	{
		if (actualLine > 0)// if we're not on the first line of the display
		{
			actualLine--;
		}
		else
		{
			actualShift--;
		}
	}
	display();
}

void Menu::selectLine()
{
	if (!enabled)return;
	int type = (firstItem + actualShift + actualLine)->itemType;
	if (selected)
	{
		selected = 0;
	}
	else if (type == MENU_INT)
	{
		selected = 1;
	}
	else if (type == MENU_BUTTON)
	{
		(firstItem + actualShift + actualLine)->callback();
	}
	else if (type == MENU_TOGGLE)
	{
		(firstItem + actualShift + actualLine)->value = !(firstItem + actualShift + actualLine)->value;
	}
	display();
}

void Menu::changeVal(int v)
{
	if (!enabled)return;
	(firstItem + actualShift + actualLine)->value += v;
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