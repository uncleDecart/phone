/*
 * USART.h
 *
 *  Created on: 15 ����. 2014 �.
 *      Author: Decart
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>
#include <stdbool.h>

#define FOSC 8000000  //Clock Speed
#define BAUD 9600     //Baud rate set to 9600
#define MYBRR FOSC/16/BAUD - 1
#define UART_RX_BUFF_SIZE 16
#define MAX_CONTACT_NAME 9


char UartRxBuff[UART_RX_BUFF_SIZE];
unsigned char CurUartRxBufCursorPos;
bool UartRxBuffHasComand;

void UART_init (void);

void UART_sendChar(char data);
void UART_sendString(char* string);

char UART_getChar(void);
char* UART_getString(char string_separator);

void UART_clearRxBuff();

void UART_setupContacts(char** contactList);

#endif /* USART_H_ */
