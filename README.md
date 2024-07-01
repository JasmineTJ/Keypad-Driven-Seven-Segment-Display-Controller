## Project Overview
This project is a software solution that displays a number on a seven-segment display upon pressing a button on a keypad. It demonstrates the use of 1-D and 2-D arrays, passing arrays to functions, and the internal design of a keypad and the mechanisms used to interface it with software.

## Features
- **GPIO Driver**: A custom GPIO driver is used to interface the Keypad and the seven-segment display.
- **Keypad Driver**: The Keypad driver includes APIs for initializing the internal keypad driver variable(s) (`Keypad_init`), managing key presses (`Keypad_manage`), and retrieving the last stored key (`Keypad_GetKey`).
- **Seven Segment Display Control**: The main application uses the GPIO and Keypad functions to control a seven-segment display and display a number upon a key press.