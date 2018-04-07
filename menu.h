#pragma once
#ifndef _MENU_H
#define _MENU_H

/*******Constants********/

#define MENU_LABEL 0
#define MENU_INT 1
#define MENU_BUTTON 2
#define MENU_TOGGLE 3

/*****End Constants******/

#include <LiquidCrystal_I2C.h>

class MenuItem
{
public:
	MenuItem(char itemType, char *text);
	MenuItem(char itemType, char *text, int value, int min, int max);
	MenuItem(char itemType, char *text, void(*callback)());
	char itemType;
	char *text;
	int value;
	int _min;
	int _max;
	void(*callback)();
};

class Menu
{
public:
	Menu(int adress, int col, int row, MenuItem* firstItem, int length);
	void init();
	void display();
	void nextLine();
	void prevLine();
	void selectLine();
	LiquidCrystal_I2C lcd;
	void disable();
	void enable();
private:
	void changeVal(int v);
	MenuItem *firstItem;
	int length;
	int actualLine;
	int actualShift;
	int row;
	int selected;
	int enabled;
};

#endif