 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins ID'S */
#define LCD_RS_PORT_ID 					PORTC_ID
#define LCD_RS_PIN_ID 					PIN0_ID
#define LCD_RW 							LOGIC_LOW
#define LCD_ENABLE_PORT_ID 				PORTC_ID
#define LCD_ENABLE_PIN_ID 				PIN3_ID
#define LCD_DATA_PORT_ID 				PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD Commands */
#define LCD_COMMAND_CLEAR_SCREEN 								0x01
#define LCD_COMMAND_RETURN_HOME 								0x02
#define LCD_COMMAND_SHIFT_CURSOR_LEFT 							0x04
#define LCD_COMMAND_SHIFT_DISPLAY_RIGHT 						0x05
#define LCD_COMMAND_SHIFT_CURSOR_RIGHT 							0x06
#define LCD_COMMAND_SHIFT_DISPLAY_LEFT 							0x07
#define LCD_COMMAND_DISPLAY_OFF_CURSOR_OFF 						0x08
#define LCD_COMMAND_DISPLAY_OFF_CURSOR_ON 						0x0A
#define LCD_COMMAND_DISPLAY_ON_CURSOR_OFF 						0x0C
#define LCD_COMMAND_DISPLAY_ON_CURSOR_ON 						0x0E
#define LCD_COMMAND_DISPLAY_ON_CURSOR_BLINKING 					0x0F
#define LCD_COMMAND_SHIFT_CURSOR_POSITION_LEFT 					0x10
#define LCD_COMMAND_SHIFT_CURSOR_POSITION_RIGHT 				0x14
#define LCD_COMMAND_SHIFT_ENTIRE_DISPLAY_LEFT 					0x18
#define LCD_COMMAND_SHIFT_ENTIRE_DISPLAY_RIGHT 					0x1C
#define LCD_COMMAND_FORCE_CURSOR_FIRST_LINE 					0x80
#define LCD_COMMAND_FORCE_CURSOR_SECOND_LINE 					0xCO
#define LCD_COMMAND_TWO_LINES_5X8_MATRIX 						0x38
#define LCD_COMMAND_EIGHT_BIT_ONE_LINE 							0x30
#define LCD_COMMAND_EIGHT_BIT_TWO_LINE 							0x38
#define LCD_COMMAND_FOUR_BIT_ONE_LINE 							0x20
#define LCD_COMMAND_FOUR_BIT_TWO_LINE 							0x28
#define LCD_COMMAND_TWO_LINES_FOUR_BITS_MODE_INIT1 				0x33
#define LCD_COMMAND_TWO_LINES_FOUR_BITS_MODE_INIT2 				0x32


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 * Send the required command to the screen */

void LCD_SendCommand(uint8 command);

/* Description :
 * Display the required character on the screen */

void LCD_DisplayCharacter(uint8 character);

/* Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits. */

void LCD_init(void);

/* Description :
 * Display the required string on the screen */

void LCD_DisplayString(const char *str);

/* Description :
 * Move the cursor to a specified row and column index on the screen */

void LCD_MoveCursor(uint8 col , uint8 row);

/* Description :
 * Display the required string in a specified row and column index on the screen */

void LCD_DisplayStringRowColumn(uint8 row, uint8 col, const char *String);

/* Description :
 * Send the clear screen command */

void LCD_ClearScreen(void);

/* Description :
 * Display the required decimal value on the screen */

void LCD_IntegerToString(int data);

#endif /* LCD_H_ */
