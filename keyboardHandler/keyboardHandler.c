/*
 * keyboardHandler.c
 *
 *  Created on: 13 ����. 2014 �.
 *      Author: Decart
 */
#include "keyboardHandler.h"

char KeyboardSymbols[4][4] = {{'1', '2', '3', 'A'},
                              {'4', '5', '6', 'B'},
                              {'7', '8', '9', 'C'},
                              {'*', '0', '#', 'D'}};


char getKeyboardResponse(int portPin)
{
    if (!correctPackage(portPin))
        return INCORRECT_SYMBOL;
    char* curPackage = getBinaryRepresentation(portPin);
    unsigned col = find(1,curPackage, 0, 3);
    unsigned char row = find(1,curPackage, 4, 7);
    return KeyboardSymbols[row][col];
}
bool correctPackage(int num)
{
    return (num & 0xF0);
}
char* getBinaryRepresentation(int from)
{
    static char res[8];
    for (char i = 0; i <= 8; ++i)
        res[7 - i] = (from & (1 << i)) ? 1 : 0;
    return res;
}
unsigned char find(int num, char curPackage[], char startPos, char endPos)
{
    for(unsigned char i = startPos; i <= endPos; i++)
        if (curPackage[i] == num)
            return i - startPos;
    return 0;
}



