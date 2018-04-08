#pragma once
#ifndef _MENU_H
#define _MENU_H

/*******Constants********/

#define MENU_LABEL 0
#define MENU_INT 1
#define MENU_BUTTON 2
#define MENU_TOGGLE 3

#define BUTTONS_MENU 1
#define ROTARY_ENCODER_MENU 2

/*****End Constants******/

#include <LiquidCrystal_I2C.h>

class MenuItem
{
public:
	MenuItem(char itemType, char *text);
	MenuItem(char itemType, char *text, int value, int min, int max, int step);
	MenuItem(char itemType, char *text, void(*callback)());
	char itemType;
	char *text;
	int value;
	int _min;
	int _max;
	int step;//how much does one "next" change the value?
	void(*callback)();
};

class Menu
{
public:
	Menu(int adress, int col, int row, MenuItem* firstItem, int length);
	Menu(int adress, int col, int row, MenuItem* firstItem, int length, int type, int pinA, int pinB, int buttonPin);
	void init();
	void display();
	void nextLine();
	void prevLine();
	void selectLine();
	LiquidCrystal_I2C lcd;
	void disable();
	void enable();
	void update();
private:
	void changeVal(int v);
	MenuItem *firstItem;
	int length;//number of menu items
	int actualLine;//the row on which the arrow is
	int actualShift;//the number of the first row
	int row;//number of rows displayed at once
	int selected;
	int enabled;

	int type;
	int pinA;
	int pinB;
	int buttonPin;
	int lastA;
	int lastB;
	int lastMainButton;
};

#endif