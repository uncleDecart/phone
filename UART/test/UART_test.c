/*
 * UART_test.c
 *
 *  Created on: Nov 23, 2014
 *      Author: decart
 */
#include "UART_test.h"

void UART_test(void)
{
	execute_test_UART_sendChar();
	execute_test_UART_sendString();
	execute_test_UART_getChar();
	execute_test_UART_getString();
}

void execute_test_UART_sendChar()
{
	printStringDebug("you should see \'c\' char on UART \n \r");
	UART_sendChar('c');
}
void execute_test_UART_sendString()
{
	printStringDebug("you should see this string on UART incoming\n \r");
	UART_sendString("you should see this string on UART incoming\n \r");
}

void execute_test_UART_getChar()
{
	printStringDebug("enter char\n \r");
	char tmp = UART_getChar();
	printStringDebug("returning char is ");
	printNumberDebug(tmp);
}
void execute_test_UART_getString()
{
	printStringDebug("enter string\n \r");
	char tmp = UART_getString('\n');
	printStringDebug("returning char is ");
	printNumberDebug(tmp);
}



