/*
 * lcd.c
 *
 *  Created on: 14 ����. 2014 �.
 *      Author: Decart
 */
#include "lcd.h"


void lcd_PutNibble(char c)
{
	c <<= 4;
	LCD_E_SET;
	_delay_us(50);
	PLUG_PORT &= 0x0F;
	PLUG_PORT |= c;
	LCD_E_CLR;
	_delay_us(50);
}

void lcd_putByte(char c, char RsLineState)
{
	char highc = 0;
	highc = c >> 4;
	if (RsLineState == LCD_COMMAND)
		LCD_RS_CLR;
	else
		LCD_RS_SET;
	lcd_PutNibble(highc);
	lcd_PutNibble(c);
}

void lcd_init()
{
	_delay_ms(30);
	lcd_PutNibble(0b00000010);
	_delay_ms(30);
	lcd_putByte(0x28, LCD_COMMAND);
	_delay_ms(30);
	lcd_putByte(0x0C, LCD_COMMAND);
	_delay_ms(30);
	lcd_putByte(0x06, LCD_COMMAND);
	_delay_ms(30);
	lcd_clear();
}

void lcd_clear()
{
	lcd_putByte(0x01, LCD_COMMAND);
	_delay_us(1500);
}

void lcd_gotoxy(char col, char row)
{
	char adr;
	adr = 0x40 * row + col;
	adr|= 0x80;
	lcd_putByte(adr, LCD_COMMAND);
}

void lcd_printString(char string[])
{
	unsigned char i = 0;
	while(string[i] != '\0')
		lcd_putByte(string[i++], LCD_DATA);
}

