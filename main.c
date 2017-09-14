#include <avr/io.h>
#include <util/delay.h>
#include "keyboardHandler/keyboardHandler.h"
#include "UART/UART.h"
#include "lcd/lcd.h"
#include "menu/menu.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>


#include "keyboardHandler/test/keyboardHandlerTest.h"

#define MAX_NUMBER_LEN 11
#define DELETE_SYMBOL 'A'
#define CALL_SYMBOL 'B'
#define MENU_SYMBOL 'C'

volatile char number[MAX_NUMBER_LEN];
unsigned char curCursorPos = 0;


void initComponents()
{
	for (int i = 0; i < MAX_NUMBER_LEN; i++)
		number[i] = ' ';

	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	lcd_init();
	UART_init();
}


void printNumber()
{
	lcd_gotoxy(0, 1);

	for(unsigned char i = 0; i < MAX_NUMBER_LEN; i++)
		lcd_putByte(number[i], LCD_DATA);
}

void call()
{
    static unsigned char tries = 0;
    tries++;
	UART_sendString("atd ");
	unsigned char i = 0;
	while (number[i] != ' ' && number[i] != '\0')
	{
		UART_sendChar(number[i++]);
		_delay_ms(50);
	}
	UART_sendString(";\r");

	while(!UartRxBuffHasComand)
		_delay_ms(10);
	lcd_clear();
	lcd_printString(UartRxBuff);
	_delay_ms(2500);

    if (strstr(UartRxBuff, "OK"))
	{
    	tries = 0;
		lcd_clear();
		lcd_printString("calling");
		_delay_ms(250);
    	return;
	}
    else if (tries < 10)
	{
    	call();
    	_delay_ms(250);
	}
    else
    {
        tries = 0;
		lcd_clear();
		lcd_printString("can\'t call ");
		_delay_ms(250);
    }
}

bool SymbolInUDR()
{
	return  ( UCSRA & ( 1 << RXC ) );
}

void parseCommand()
{
    if (strstr(UartRxBuff, "RING"))
    {
    	lcd_clear();
    	lcd_printString("Ring");
    	_delay_ms(400);
		UART_sendString("ATA\r");
    }
    else if (strstr(UartRxBuff, "^RSSI:"))
    {
    	lcd_gotoxy(0,0);
    	lcd_printString("Signal ");
    	char *tmp = strstr(UartRxBuff, "^RSSI:");
    	tmp += 6;
       	lcd_putByte(*tmp, LCD_DATA);
       	tmp++;
       	lcd_putByte(*tmp, LCD_DATA);
    	_delay_ms(500);
    }
    UART_clearRxBuff();
}

void checkUART()
{
	if (UartRxBuffHasComand) parseCommand();
}


int main()
{
	sei();
	initComponents();
	while(1)
	{
		for (char i = 1; i < 16; i *= 2)
		{
			PORTB = i;
			checkUART();
			char curSymb = getKeyboardResponse(PINB);
			switch(curSymb)
			{
			case CALL_SYMBOL:
				call();
				break;

			case INCORRECT_SYMBOL:
				break;

			case DELETE_SYMBOL:

				if (curCursorPos > 0)
					number[--curCursorPos] = ' ';
				printNumber();
				break;

			case MENU_SYMBOL:
				openMenu();
				break;

			default :
				if (curCursorPos <  MAX_NUMBER_LEN)
					number[curCursorPos++] = curSymb;
				printNumber();
				break;
			}
			_delay_ms(50);
		}
	}
	return 0;
}
