/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "gpio.h" /* To use the GPIO Functions */
#include "lcd.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <util/delay.h> /* To use delay */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LCD_SendCommand(uint8 command)
{
	GPIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if (LCD_DATA_BITS_MODE ==4)
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */


#elif (LCD_DATA_BITS_MODE ==8)
	GPIO_WritePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_DisplayCharacter(uint8 character)
{
	GPIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Instruction Mode RS=1 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if (LCD_DATA_BITS_MODE ==4)
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,4));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,5));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,6));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */


#elif (LCD_DATA_BITS_MODE ==8)
	GPIO_WritePort(LCD_DATA_PORT_ID,character); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_WritePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	GPIO_SetPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,PIN_OUTPUT);
	_delay_ms(20); 	/* LCD Power ON delay always > 15ms */

#if (LCD_DATA_BITS_MODE ==4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_SetPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_SetPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_SendCommand(LCD_COMMAND_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_COMMAND_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(LCD_COMMAND_FOUR_BIT_TWO_LINE);


#elif (LCD_DATA_BITS_MODE ==8)
	/* Configure the data port as output port */
	GPIO_SetupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(LCD_COMMAND_EIGHT_BIT_TWO_LINE);
#endif
	LCD_SendCommand(LCD_COMMAND_DISPLAY_ON_CURSOR_OFF); /* cursor off */
	LCD_SendCommand(LCD_COMMAND_CLEAR_SCREEN); /* clear LCD at the beginning */
}

void LCD_DisplayString(const char *str)
{
	uint8 counter=0;
	while (str[counter] != '\0'){
		LCD_DisplayCharacter(str[counter]);
		counter++;
	}
}

void LCD_MoveCursor(uint8 col , uint8 row)
{
	uint8 lcd_address;

	switch(row)
	{
	case 0:
		lcd_address = col;
		break;
	case 1:
		lcd_address = col + 0x40;
		break;
	case 2:
		lcd_address = col + 0x10;
		break;
	case 3:
		lcd_address = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_SendCommand(lcd_address | LCD_COMMAND_FORCE_CURSOR_FIRST_LINE);
}

void LCD_DisplayStringRowColumn(uint8 row, uint8 col, const char *String)
{
	LCD_MoveCursor(col,row); /* go to to the required LCD position */
	LCD_DisplayString(String); /* display the string */

}

void LCD_ClearScreen(void)
{
	LCD_SendCommand(LCD_COMMAND_CLEAR_SCREEN); /* Send clear display command */
}

void LCD_IntegerToString(int data)
{
	uint8 buff[16]; /* String to hold the ascii result */
	itoa(data , buff , 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_DisplayString(buff); /* Display the string */
}
