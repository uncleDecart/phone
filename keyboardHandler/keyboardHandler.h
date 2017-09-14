/*
 * keyboardHandler.h
 *
 *  Created on: 13 ����. 2014 �.
 *      Author: Decart
 */

#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <stdbool.h>

#define INCORRECT_SYMBOL 'F'

char getKeyboardResponse(int portPin);
char* getBinaryRepresentation(int from);
unsigned char find(int num, char curPackage[], char startPos, char endPos);
bool correctPackage(int num);


#endif /* KEYBOARDHANDLER_H */
