/*
 * menu.c
 *
 *  Created on: May 2, 2015
 *      Author: decart
 */
#include "menu.h"

#include <stdbool.h>
#include "../keyboardHandler/keyboardHandler.h"
#include "../UART/UART.h"

#define KEY_UP '2'
#define KEY_DOWN '8'
#define EXIT_KEY 'A'
#define OK_KEY '5'

#define MAX_COL 16
#define MAX_MENU_ROW 3
#define MAX_CONTACTS_ROW 3
char MenuRows[MAX_MENU_ROW][MAX_COL] = {"Contacts", "SMS", "Settings"};
char ContactsRows[MAX_CONTACTS_ROW][MAX_COL];// = {"Bob", "Jack", "Christian"};
volatile bool OkKeyPressed = false;


void printMenuRows(unsigned char curRow, unsigned char maxRow ,char menu[][MAX_COL])
{
	lcd_clear();
	lcd_putByte('*', LCD_DATA);
	lcd_printString(menu[curRow]);
	lcd_gotoxy(0, 1);
	if (curRow < maxRow - 1)
	{
		lcd_putByte(' ', LCD_DATA);
		lcd_printString(menu[curRow + 1]);
	}
	else
		lcd_printString("================");
}
char* getNumber(unsigned char contactdId)
{
	return "88005553535";
}


void contactsSubMenu()
{
	lcd_clear();
	bool QuitSubMenu = false;
	unsigned char curSubRow = 0;

	while(!QuitSubMenu)
	{
		for (char i = 1; i < 16; i *= 2)
		{
			PORTB = i;
			lcd_putByte(48, LCD_DATA);
			char curSymb = getKeyboardResponse(PINB);
			lcd_clear();

			if (curSymb == KEY_UP && curSubRow > 0)
				curSubRow--;
			if (curSymb == KEY_DOWN && curSubRow < MAX_CONTACTS_ROW - 1)
				curSubRow++;
			if (curSymb == EXIT_KEY)
				QuitSubMenu = true;
			if (curSymb == OK_KEY);
				//call(getNumber(curSubRow));

			printMenuRows(curSubRow, MAX_CONTACTS_ROW ,ContactsRows);
			_delay_ms(50);
		}
	}
}

void smsSubMenu()
{
	lcd_clear();
	lcd_printString("SMS");
	_delay_ms(1500);
}

void settingsSubMenu()
{
	lcd_clear();
	lcd_printString("Settings");
	_delay_ms(1500);
}

void printSubMenu(unsigned char curRow)
{
	OkKeyPressed = false;
	if (curRow == 0)
		contactsSubMenu();
	if (curRow == 1)
		smsSubMenu();
	if (curRow == 2)
		settingsSubMenu();
}


void openMenu()
{
	unsigned char curRow = 0;
	bool QuitMenu = false;
	while(!QuitMenu)
	{
		for (char i = 1; i < 16; i *= 2)
		{
			PORTB = i;
			lcd_putByte(48, LCD_DATA);
			char curSymb = getKeyboardResponse(PINB);
			lcd_clear();

			if (curSymb == KEY_UP && curRow > 0)
				curRow--;
			if (curSymb == KEY_DOWN && curRow < MAX_MENU_ROW - 1)
				curRow++;
			if (curSymb == EXIT_KEY)
				QuitMenu = true;
			if (curSymb == OK_KEY)
				OkKeyPressed = true;

			if (OkKeyPressed)
				printSubMenu(curRow);
			else
				printMenuRows(curRow, MAX_MENU_ROW ,MenuRows);
			_delay_ms(50);
		}
	}

}
