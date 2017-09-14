/*
 * test.c
 *
 *  Created on: Dec 16, 2014
 *      Author: decart
 */

#include "testUtilities.h"

void initTestUtilities()
{
	UART_init();
}

void printStringDebug(char* string)
{
	UART_sendString(string);
}

void printNumberDebug(char num)
{
	UART_sendChar(num);
}


