 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define STANDARD_KEYPAD
#undef STANDARD_KEYPAD

#define KEYPAD_NUM_ROWS 4
#define KEYPAD_NUM_COLUMNS 4

#define KEYPAD_ROW_PORT_ID PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID PIN4_ID

#define KEYPAD_COLUMN_PORT_ID PORTD_ID
#define KEYPAD_FIRST_COLUMN_PIN_ID PIN4_ID

#define KEYPAD_BUTTON_PRESSED LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH

#define KEYPAD_NOT_PRESSED 0xFF


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 KEYPAD_GetPressedKey(void);
#endif /* KEYPAD_H_ */
