#include "UART.h"
#include <avr/interrupt.h>


#include <stdlib.h>
#include <string.h>

void UART_init (void)
{
	UBRRH=0x00;
	UBRRL = MYBRR; //the baud rate
	UCSRA = 0b00000000;
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE ); //Enable receiver and transmitter
	UCSRC = 0x86;

	UartRxBuffHasComand = false;
	CurUartRxBufCursorPos = 0;
	for (unsigned char i = 0; i < UART_RX_BUFF_SIZE; i++)
		UartRxBuff[i] = 'F';
}

ISR( USART_RXC_vect )
{
  unsigned char rxbyte = UDR;
  if (rxbyte == '\r')
	  UartRxBuffHasComand = true;
  if(CurUartRxBufCursorPos != UART_RX_BUFF_SIZE)
	  UartRxBuff[CurUartRxBufCursorPos++] = rxbyte;
  else if (!UartRxBuffHasComand)
	  UART_clearRxBuff();
}

void UART_clearRxBuff()
{
	for(unsigned char i = 0; i < UART_RX_BUFF_SIZE; i++)
		UartRxBuff[i] = 0;
	CurUartRxBufCursorPos = 0;
	UartRxBuffHasComand = false;
}


void UART_sendChar(char data)
{
     while(!(UCSRA & (1 << UDRE))); //Wait until transmit buffer is empty
     UDR = data;
}

void UART_sendString(char* string)
{
	while(*string != '\0')
	{
		UART_sendChar(*string++);
		_delay_ms(50);
	}
}
char UART_getChar(void)
{
     while(!(UCSRA & (1 << RXC))); //Wait until data is received
     return UDR; //Get the data from buffer and return it
}

char* UART_getString(char string_separator)
{
	char* res = (char *)malloc(sizeof(char));
	char curSymbol;
	unsigned char i = 0;
	do
	{
		curSymbol = UART_getChar();
		res = (char *)realloc(res, sizeof(res) * i);
		res[i++] = curSymbol;
	}
	while(curSymbol != string_separator);
	return res;
}

const unsigned char getContactsAmount()
{
	int res = 0;
	char tries = 0;
	unsigned char i = 100;
	while(!UartRxBuffHasComand && strstr(UartRxBuff, "+CPBS: ") && tries++ < 5 )
	{
		UART_sendString("AT+CPBS?");
		_delay_ms(250);
	}
	if (tries >= 4) return 0;
	else
	{
		char *tmp = strstr(UartRxBuff, ",");
		tmp++;
	    while (*tmp != ',')
	    {
	        res += (*tmp - 48 ) * i;
	        i /= 10;
	        tmp++;
	    }
	}
    if (i != 0) return (unsigned char)(res/(i * 10));
	return (unsigned char)res;
}

