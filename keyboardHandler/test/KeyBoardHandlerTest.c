/*
 * KeyBoardHandlerTest.c
 *
 *  Created on: Nov 23, 2014
 *      Author: decart
 */

#include "keyboardHandlerTest.h"

bool TestKeyboardHandler()
{
	initTestUtilities();
	if (executeTestGetBinaryRepresentation() &&
		executeTestFind() &&
		executeTestIsCorrectPackage &&
		executeTestGetKeyboardResponse())
	{
		printStringDebug("TestKeyboradHandler() passed \r\n");
		return true;
	}
	printStringDebug("TestKeyboradHandler() failed \r\n");
	return false;
}

bool executeTestGetBinaryRepresentation()
{
	char exp[]  = {0, 0, 0, 0, 1, 0, 1, 0};
    char exp1[] = {1, 1, 1, 1, 1, 1, 1, 1};
    char exp2[] = {0, 0, 0, 0, 0, 0, 1, 0};
    char exp3[] = {0, 1, 1, 1, 1, 0, 1 ,1};

    if (testGetBinaryRepresentation(10, exp) && testGetBinaryRepresentation(255, exp1) &&
        testGetBinaryRepresentation(2, exp2) && testGetBinaryRepresentation(123, exp3))
    {
        printStringDebug("testGetBinaryRepresentation() passed \r\n");
        return true;
    }
	printStringDebug("testGetBinaryRepresentation() failed \r\n");
	return false;
}
bool testGetBinaryRepresentation(char num, char* exp)
{
    char getBinaryRepresentationArraySize = 8;
    char* act = getBinaryRepresentation(num);
    return (compareArrays(act, exp, getBinaryRepresentationArraySize));
}
bool compareArrays(char from[], char to[], char size)
{
    for (int i = 0; i < size; i++)
        if (from[i] != to[i])
            return false;
    return true;
}

bool executeTestFind()
{
    char tmp[] = {1, 9, 8, 7, 6};
    if ( testFind(1, tmp, 0, 3, 0) && testFind(8, tmp, 1, 4, 1))
    {
    	printStringDebug("testFind() passed\r\n");
    	return true;
    }
	printStringDebug("testFind() failed\r\n");
    return false;
}
bool testFind(int num, char package[], char startPos, char endPos, int exp)
{
	return (find(num, package , startPos, endPos) == exp);
}

bool executeTestIsCorrectPackage()
{
	int tmp = 0b01000000;
	int tmp1 = 0b01000100;
	if (!correctPackage(tmp) && correctPackage(tmp1))
	{
		printStringDebug("testIsCorrectPackage() passed\n\r");
		return true;
	}
	printStringDebug("testIsCorrectPackage() failed\n\r");
	return false;
}

bool executeTestGetKeyboardResponse()
{
	if ((getKeyboardResponse(0b10001000) == '1') &&
		(getKeyboardResponse(0b00010001) == 'D') &&
		(getKeyboardResponse(0b00001000) == INCORRECT_SYMBOL))
	{
		printStringDebug("testGetKeyboardResponse() passed \n\r");
		return true;
	}
	printStringDebug("testGetKeyboardResponse() failed \n\r");
	return false;
}


bool testButtonPressed()
{
	printStringDebug("Please Press \'3\' button in 10 sec \r\n");
	for (char i = 0; i <= 9; i++)
	{
		PORTB = 0b00100000;
		if (getKeyboardResponse(PINB) == '3')
			return true;
		printNumberDebug((9 - i) + 48);
		printNumberDebug(getKeyboardResponse(PINB));
		_delay_ms(1000);
	}
	printStringDebug("testButttonPressed failed \r\n");
	return false;
}


void seeKeyboard()
{
	for (int i = 1; i < 16; i *= 2)
	{
		for (int j = 16; j <= 128; j *= 2)
			printNumberDebug(getKeyboardResponse(i | j));
		printStringDebug("\r\n");
	}
}

void KeyboardDebugMode()
{
	while(1)
	{
		for (char i = 1; i < 16; i *= 2)
		{
			PORTB = i;
			char *tmp = getBinaryRepresentation(PINB);
			for (unsigned char j = 0; j < 8; j++)
				printNumberDebug(tmp[j] + 48);
			printStringDebug(" ");
			char curSymb = getKeyboardResponse(PINB);
			printNumberDebug(curSymb);
			_delay_ms(250);
		}
	}
}
