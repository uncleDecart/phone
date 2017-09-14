/*
 * lcd.h
 *
 *  Created on: 14 ����. 2014 �.
 *      Author: Decart
 */

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>

#define PLUG_PORT PORTD

#define LCD_E_SET PLUG_PORT |= 0x08
#define LCD_E_CLR PLUG_PORT &= 0xF7
#define LCD_RS_SET PLUG_PORT |= 0x04
#define LCD_RS_CLR PLUG_PORT &= 0xFB

#define LCD_COMMAND 0
#define LCD_DATA 1

void lcd_init();
void lcd_clear();
void lcd_gotoxy(char col, char row);
void lcd_printString (char string[]);
void lcd_putByte(char c, char RsLineState);


#endif /* LCD_H */
