
/**
 * Keypad.h
 *
 *  Created on: Thu Apr 27 2023
 *  Author    : Abdullah Darwish
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include "Gpio.h"

#define COL_PORT  GPIO_B
#define COL_START_INDEX 0
#define COL_END_INDEX 2

#define ROW_PORT GPIO_B
#define ROW_START_INDEX 5
#define ROW_END_INDEX 8



// provided api functions
void Keypad_Init(void);

void Keypad_Manage(void);

uint8 Keypad_GetKey(void);


// required function implemented by applicaiton
void KeypadCallout_KeyPressNotificaton();


#endif /* KEYPAD_H */
