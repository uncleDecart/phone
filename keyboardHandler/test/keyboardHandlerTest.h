/*
 * keyboardHandlerTest.h
 *
 *  Created on: Nov 23, 2014
 *      Author: decart
 */

#ifndef KEYBOARDHANDLER_TEST_KEYBOARDHANDLERTEST_H_
#define KEYBOARDHANDLER_TEST_KEYBOARDHANDLERTEST_H_

#include "keyboardHandlerTest.h"
#include <stdbool.h>
#include "../keyboardHandler.h"
#include "../../testUtilities/testUtilities.h"

bool TestKeyboardHandler();

bool executeTestGetKeyboardResponse();
bool testGetBinaryRepresentation(char num, char* exp);
bool compareArrays(char from[], char to[], char size);

bool executeTestGetBinaryRepresentation();

bool executeTestFind();


bool executeTestIsCorrectPackage();

bool testFind(int num, char package[], char startPos, char endPos, int exp);


bool testButtonPressed();


void seeKeyboard();

void KeyboardDebugMode();

#endif /* KEYBOARDHANDLER_TEST_KEYBOARDHANDLERTEST_H_ */
