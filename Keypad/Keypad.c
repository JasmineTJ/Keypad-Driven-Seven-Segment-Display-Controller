/**
 * Keypad.c
 *
 *  Created on: Thu Apr 27 2023
 *  Author : Abdullah Darwish
 */
#include "Keypad.h"
#include "Gpio.h"
#include "Std_Types.h"

// Define the keypad layout
static const uint8 KEYPAD[4][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {0, 0, 0}
};

// Global variable to store the key pressed
uint8 key_pressed = '\0';  // Initialize to '\0' to indicate 'no key'
uint8 is_key_pressed = 0;
uint8 key_release_count = 0;  // Count the number of scans where the key is not registered as pressed

void Keypad_Init(void)
{
    uint8 index = 0;
    // config columns
    for(index = COL_START_INDEX; index <= COL_END_INDEX; index++){
        Gpio_ConfigPin(COL_PORT, index, GPIO_INPUT, GPIO_PULL_UP);
    }

    //config rows
    for(index = ROW_START_INDEX; index <= ROW_END_INDEX; index++){
        Gpio_ConfigPin(ROW_PORT, index, GPIO_OUTPUT, GPIO_PUSH_PULL);
    }

    // put idle state for output pins
    for(index = ROW_START_INDEX; index <= ROW_END_INDEX; index++){
        Gpio_WritePin(ROW_PORT, index, HIGH);
    }
}

void Keypad_Manage(void)
{
    uint8 row, col;

    // Scan all keys to check which one is pressed
    for (row = ROW_START_INDEX; row <= ROW_END_INDEX; row++) {
        Gpio_WritePin(ROW_PORT, row, LOW);  // Activate the row

        for (col = COL_START_INDEX; col <= COL_END_INDEX; col++) {
            if (Gpio_ReadPin(COL_PORT, col) == LOW) {  // If the key is pressed
                // Only a transition from no key pressed to one key press shall be considered as a valid press
                if (!is_key_pressed) {
                    // Store the pressed key value
                    key_pressed = KEYPAD[row - ROW_START_INDEX][col - COL_START_INDEX];
                    is_key_pressed = 1;
                    key_release_count = 0;

                    // Call a function “KeypadCallouts_KeyPressNotificaton”
                    KeypadCallout_KeyPressNotificaton();
                }
            } else {
                // Increment the key release count
                key_release_count++;

                // If the key is not registered as pressed for 5 consecutive scans, consider it released
                if (key_release_count >= 5) {
                    is_key_pressed = 0;
                    key_pressed = '\0';  // Reset the stored key
                    key_release_count = 0;
                }
            }
        }

        Gpio_WritePin(ROW_PORT, row, HIGH);  // Deactivate the row
    }
}

uint8 Keypad_GetKey(void)
{
    // Return the last stored key
    return key_pressed;
}
